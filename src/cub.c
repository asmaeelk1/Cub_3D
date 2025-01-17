/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:29:40 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/17 10:17:36 by oel-feng         ###   ########.fr       */
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

// void	__attribute__ ((destructor)) _leaks(void)
// {
// 	system("leaks cub3D");
// }

static void	set_data(t_map_data *map_data)
{
	map_data->colors = gcollector(sizeof(t_colors), 1);
	map_data->data_mlx = gcollector(sizeof(t_mlx_data), 1);
	map_data->textures = gcollector(sizeof(t_textures), 1);
	map_data->map = NULL;
	map_data->arr_text = NULL;
	map_data->player = gcollector(sizeof(t_player), 1);
	map_data->player->player = '\0';
	map_data->player->if_player_exist = false;
	map_data->p_x_pos = 0;
	map_data->p_y_pos = 0;
	map_data->wall = false;
	map_data->player->rotate_angle = M_PI / 2;
	map_data->player->rotation_speed = 2 * ( M_PI / 180);
	
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
	init_mlx = init_mlx_data(&map_data);
	raycasting_init(cast);
	if (init_mlx)
	{
		gcollector(0, 0);
		exit(EXIT_FAILURE);
	}
	// draw 2d_map
	// draw_square(map_data);
	// raycasting(&map_data);

	start_raycast(&map_data);

	// map_2d(&map_data);
	mlx_loop_hook(map_data->data_mlx->mlx, (void *)my_keyhook, &map_data);
	mlx_loop(map_data->data_mlx->mlx);
	cleanup_and_exit(&map_data);
}
