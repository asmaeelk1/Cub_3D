/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghriyba <ghriyba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:29:40 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/01 02:48:14 by ghriyba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub_bonus.h"

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
	data->text = mlx_load_png(data->frames[0]);
	data->img_frame = mlx_texture_to_image(data->mlx, data->text);
	mlx_image_to_window(data->mlx, data->mini_map, 0, 0);
	mlx_image_to_window(data->mlx, data->img_frame,  740, 717);
	return (0);
}

static void	int_arr_frames(t_map_data *data) 
{
	int i;
	int index_frame;
	char *path;

	i = -1;
	index_frame = 1;
	while(++i < 61)
	{
		path = "cub_bonus/frames/frame_";
		path = ft_strjoin(path, ft_itoa(index_frame));
		data->frames[i] = ft_strjoin(path, ".png");
		index_frame++;
	}
	data->animation_playing = false;
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
	map_data->door = gcollector(sizeof(t_door), 1);
	map_data->door->x = -1;
    map_data->door->y = -1;
    map_data->door->progress = 0.0;
    map_data->door->state = 0;
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

static void	start_textures(t_map_data *map_data)
{
	map_data->textures[NORTH] = mlx_load_png(map_data->texts->north);
	map_data->textures[SOUTH] = mlx_load_png(map_data->texts->south);
	map_data->textures[WEST] = mlx_load_png(map_data->texts->west);
	map_data->textures[EAST] = mlx_load_png(map_data->texts->east);
	if (!map_data->textures[NORTH] || !map_data->textures[SOUTH]
		|| !map_data->textures[WEST] || !map_data->textures[EAST])
		ft_err("Error: Failed to load textures");
	map_data->tex_width = map_data->textures[NORTH]->width;
	map_data->tex_height = map_data->textures[NORTH]->height;
}

int	main(int ac, char **av)
{
	t_map_data	map_data;

	if (ac < 2)
		return (EXIT_FAILURE);
	set_data(&map_data);
	parsing(av[1], &map_data);
	set_plane_rotation(&map_data);
	int_arr_frames(&map_data);
	if (init_mlx_data(&map_data) == 1)
	{
		gcollector(0, 0);
		exit(EXIT_FAILURE);
	}
	start_textures(&map_data);
	map_data.map[(int)map_data.player->y_pos_map]
	[(int)map_data.player->x_pos_map] = '0';
	mlx_set_cursor_mode(map_data.mlx, MLX_MOUSE_DISABLED);
	mlx_key_hook(map_data.mlx, hook_change, &map_data);
	mlx_cursor_hook(map_data.mlx, mouse_hook, &map_data);
	mlx_loop_hook(map_data.mlx, my_keyhook, &map_data);
	mlx_loop(map_data.mlx);
	cleanup_and_exit(&map_data);
}
