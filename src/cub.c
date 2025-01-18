/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:29:40 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/18 17:19:30 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_mlx_data(t_map_data **data)
{
	(*data)->data_mlx->mlx = mlx_init((*data)->width_map * TILE_SIZE, (*data)->height_map * TILE_SIZE, "Cub_3D", true);
	if (!((*data)->data_mlx->mlx))
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (1);
	}
	(*data)->data_mlx->image = mlx_new_image((*data)->data_mlx->mlx, (*data)->width_map * TILE_SIZE,
			(*data)->height_map * TILE_SIZE);
	if (!((*data)->data_mlx->image))
	{
		mlx_close_window((*data)->data_mlx->mlx);
		return (1);
	}
	if (mlx_image_to_window((*data)->data_mlx->mlx, (*data)->data_mlx->image, 0,
			0) == -1)
	{
		mlx_close_window((*data)->data_mlx->mlx);
		return (1);
	}
	return (0);
}

void	cleanup_and_exit(t_map_data **data)
{
	mlx_terminate((*data)->data_mlx->mlx);
	gcollector(0, 0);
	exit(EXIT_SUCCESS);
}

static void	set_data(t_map_data *map_data)
{
	map_data->colors = gcollector(sizeof(t_colors), 1);
	map_data->data_mlx = gcollector(sizeof(t_mlx_data), 1);
	map_data->texts = gcollector(sizeof(t_text_map), 1);
	map_data->map = NULL;
	map_data->arr_text = NULL;
	map_data->player = gcollector(sizeof(t_player), 1);
	map_data->player->player = '\0';
	map_data->player->if_player_exist = false;
	map_data->p_x_pos = 0;
	map_data->p_y_pos = 0;
	map_data->wall = false;
	map_data->speed = 1.0;
	map_data->keys = (t_keys){0};
}

void	start_textures(t_map_data *map_data)
{
	map_data->textures[0] = mlx_load_png("textures/test.png");
	map_data->textures[1] = mlx_load_png("textures/test.png");
	map_data->textures[2] = mlx_load_png("textures/test.png");
	map_data->textures[3] = mlx_load_png("textures/test.png");
	if (!map_data->textures[0] || !map_data->textures[1] || !map_data->textures[2] || !map_data->textures[3])
		ft_err("Error: Failed to load textures");
	map_data->tex_width = map_data->textures[0]->width;
	map_data->tex_height = map_data->textures[0]->height;
}

static void	set_plane_rotation(t_map_data *map_data)
{
	if (map_data->player->player == 'N')
	{
		map_data->player->rotate_angle = 3 * M_PI / 2;
        map_data->player->dirX = 0;
        map_data->player->dirY = -1;
		map_data->player->planeX = 0.66;
        map_data->player->planeY = 0;
	}
	else if (map_data->player->player == 'S')
	{
		map_data->player->rotate_angle = M_PI / 2;
		map_data->player->dirX = 0;
		map_data->player->dirY = 1;
		map_data->player->planeX = -0.66;
		map_data->player->planeY = 0;
	}
	else if (map_data->player->player == 'E')
	{
		map_data->player->rotate_angle = 0;
        map_data->player->dirX = 1;
        map_data->player->dirY = 0;
        map_data->player->planeX = 0;
        map_data->player->planeY = 0.66;
	}
	else if (map_data->player->player == 'W')
	{
		map_data->player->rotate_angle = M_PI;
		map_data->player->dirX = -1;
		map_data->player->dirY = 0;
		map_data->player->planeX = 0;
		map_data->player->planeY = -0.66;
	}
	 map_data->player->rotation_speed = 2 * (M_PI / 180);
}

void key_hook(mlx_key_data_t keydata, void *data)
{
    t_map_data  *map_data;

	map_data = (t_map_data*)data;
    if (keydata.action == MLX_PRESS)
    {
        if (keydata.key == MLX_KEY_W)
            map_data->keys.w_pressed = true && printf("W pressed\n");
        if (keydata.key == MLX_KEY_S)
            map_data->keys.s_pressed = true && printf("S pressed\n");
        if (keydata.key == MLX_KEY_A)
            map_data->keys.a_pressed = true && printf("A pressed\n");
        if (keydata.key == MLX_KEY_D)
            map_data->keys.d_pressed = true && printf("D pressed\n");
        if (keydata.key == MLX_KEY_LEFT)
            map_data->keys.left_pressed = true && printf("LEFT pressed\n");
        if (keydata.key == MLX_KEY_RIGHT)
            map_data->keys.right_pressed = true && printf("RIGHT pressed\n");
    }
    if (keydata.action == MLX_RELEASE)
    {
        if (keydata.key == MLX_KEY_W)
            map_data->keys.w_pressed = false && printf("W released\n");
        if (keydata.key == MLX_KEY_S)
            map_data->keys.s_pressed = false && printf("S released\n");
        if (keydata.key == MLX_KEY_A)
            map_data->keys.a_pressed = false && printf("A released\n");
        if (keydata.key == MLX_KEY_D)
            map_data->keys.d_pressed = false && printf("D released\n");
        if (keydata.key == MLX_KEY_LEFT)
            map_data->keys.left_pressed = false && printf("LEFT released\n");
        if (keydata.key == MLX_KEY_RIGHT)
            map_data->keys.right_pressed = false && printf("RIGHT released\n");
    }
}

int	main(int ac, char **av)
{
	int			init_mlx;
	t_map_data	*map_data;
	t_cast		*cast;

	
	if (ac < 2)
		return (EXIT_FAILURE);
	cast = NULL;
	map_data = gcollector(sizeof(t_map_data), 1);
	set_data(map_data);
	parsing(av[1], &map_data);
	set_plane_rotation(map_data);
	init_mlx = init_mlx_data(&map_data);
	// raycasting_init(cast);
	if (init_mlx)
	{
		gcollector(0, 0);
		exit(EXIT_FAILURE);
	}
	// draw 2d_map
	// draw_square(map_data);
	// raycasting(&map_data);
	start_textures(map_data);
	start_raycast(&map_data);

	// map_2d(&map_data);
	map_data->map[map_data->player->y_pos_map][map_data->player->x_pos_map] = '0';
	mlx_key_hook(map_data->data_mlx->mlx, (void *)movement_hook, map_data);
	mlx_loop_hook(map_data->data_mlx->mlx, (void *)my_keyhook, &map_data);
	mlx_loop(map_data->data_mlx->mlx);
	cleanup_and_exit(&map_data);
}
