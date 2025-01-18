/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:29:40 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/18 20:37:39 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_mlx_data(t_map_data *data)
{
	data->data_mlx->mlx = mlx_init(WIDTH, HEIGHT, "Cub_3D", true);
	if (!(data->data_mlx->mlx))
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (1);
	}
	data->data_mlx->image = mlx_new_image(data->data_mlx->mlx, WIDTH,
			HEIGHT);
	if (!(data->data_mlx->image))
	{
		mlx_close_window(data->data_mlx->mlx);
		return (1);
	}
	if (mlx_image_to_window(data->data_mlx->mlx, data->data_mlx->image, 0,
			0) == -1)
	{
		mlx_close_window(data->data_mlx->mlx);
		return (1);
	}
	return (0);
}

void	cleanup_and_exit(t_map_data *data)
{
	mlx_terminate(data->data_mlx->mlx);
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
	map_data->keys = (t_keys){0};
}

// void	start_textures(t_map_data *map_data)
// {
// 	map_data->textures.north = mlx_load_png("textures/test.png");
// 	map_data->textures.east = mlx_load_png("textures/test.png");
// 	map_data->textures.south = mlx_load_png("textures/test.png");
// 	map_data->textures.west = mlx_load_png("textures/test.png");
// 	if (!map_data->textures.north || !map_data->textures.east
// 		|| !map_data->textures.south || !map_data->textures.west)
// 		ft_err("Error: Failed to load textures");
// }

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
        map_data->player->dirX = 0;
        map_data->player->dirY = -1;
		map_data->player->planeX = 0.66;
        map_data->player->planeY = 0;
	}
	else if (map_data->player->player == 'S')
	{
		map_data->player->dirX = 0;
		map_data->player->dirY = 1;
		map_data->player->planeX = -0.66;
		map_data->player->planeY = 0;
	}
	else if (map_data->player->player == 'E')
	{
        map_data->player->dirX = 1;
        map_data->player->dirY = 0;
        map_data->player->planeX = 0;
        map_data->player->planeY = 0.66;
	}
	else if (map_data->player->player == 'W')
	{
		map_data->player->dirX = -1;
		map_data->player->dirY = 0;
		map_data->player->planeX = 0;
		map_data->player->planeY = -0.66;
	}
	map_data->speed = 0.1;
	map_data->player->rotation_speed = 0.25;
}


int	main(int ac, char **av)
{
	t_map_data	map_data;
	t_cast		*cast;

	
	if (ac < 2)
		return (EXIT_FAILURE);
	cast = NULL;
	set_data(&map_data);
	parsing(av[1], &map_data);
	set_plane_rotation(&map_data);
	if (init_mlx_data(&map_data) == 1)
	{
		gcollector(0, 0);
		exit(EXIT_FAILURE);
	}
	start_textures(&map_data);
	map_data.map[(int)map_data.player->y_pos_map][(int)map_data.player->x_pos_map] = '0';
	mlx_loop_hook(map_data.data_mlx->mlx, my_keyhook, &map_data);
	mlx_loop(map_data.data_mlx->mlx);
	cleanup_and_exit(&map_data);
}
