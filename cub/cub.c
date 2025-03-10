/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:29:40 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/05 03:15:17 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub.h"

static int	init_mlx_data(t_map_data *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!(data->mlx))
		return (ft_putstr_fd(mlx_strerror(mlx_errno), 2), 1);
	data->image = mlx_new_image(data->mlx, WIDTH,
			HEIGHT);
	if (!(data->image))
		return (mlx_close_window(data->mlx), 1);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
		return (mlx_close_window(data->mlx), 1);
	data->mini_map = mlx_new_image(data->mlx, 200, 200);
	mlx_image_to_window(data->mlx, data->mini_map, 0, 0);
	return (0);
}

static void	cleanup_and_exit(t_map_data *data)
{
	mlx_terminate(data->mlx);
	gcollector(0, 0);
	exit(EXIT_SUCCESS);
}

static void	set_data(t_map_data *map_data)
{
	map_data->texts = gcollector(sizeof(t_textures), 1);
	map_data->player = gcollector(sizeof(t_player), 1);
	map_data->colors = gcollector(sizeof(t_colors), 1);
	map_data->player->if_player_exist = false;
	map_data->player->player = '\0';
	map_data->map = NULL;
	map_data->colors->c_ceiling = -1;
	map_data->colors->c_floor = -1;
	map_data->texts->east = NULL;
	map_data->texts->west = NULL;
	map_data->texts->north = NULL;
	map_data->texts->south = NULL;
}

int	main(int ac, char **av)
{
	t_map_data	map_data;

	if (ac < 2)
		return (EXIT_FAILURE);
	set_data(&map_data);
	parsing(av[1], &map_data);
	set_plane_rotation(&map_data);
	if (init_mlx_data(&map_data) == 1)
	{
		gcollector(0, 0);
		exit(EXIT_FAILURE);
	}
	start_textures(&map_data);
	map_data.map[(int)map_data.player->y_pos_map]
	[(int)map_data.player->x_pos_map] = '0';
	mlx_loop_hook(map_data.mlx, my_keyhook, &map_data);
	mlx_loop(map_data.mlx);
	cleanup_and_exit(&map_data);
}
