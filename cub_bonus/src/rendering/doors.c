/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:54:27 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/02 21:58:10 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

void	is_open(t_map_data *map_data, int player_x, int player_y)
{
	if (map_data->map[player_y][player_x] == 'D')
	{
		map_data->map[player_y][player_x] = '2';
		map_data->door->x = player_x;
		map_data->door->y = player_y;
		map_data->door->state = 1;
	}
	else if (map_data->map[player_y][player_x] == '2')
	{
		map_data->map[player_y][player_x] = 'D';
		map_data->door->x = player_x;
		map_data->door->y = player_y;
		map_data->door->state = 3;
	}
}

void	open_door(t_map_data *map_data, t_player *player)
{
	int	player_x;
	int	player_y;

	player_x = (int)player->x_pos_map;
	player_y = (int)player->y_pos_map;
	if (map_data->map[player_y][player_x + 1] == 'D')
		is_open(map_data, player_x + 1, player_y);
	else if (map_data->map[player_y][player_x - 1] == 'D')
		is_open(map_data, player_x - 1, player_y);
	else if (map_data->map[player_y + 1][player_x] == 'D')
		is_open(map_data, player_x, player_y + 1);
	else if (map_data->map[player_y - 1][player_x] == 'D')
		is_open(map_data, player_x, player_y - 1);
}

void	close_door(t_map_data *map_data, t_player *player)
{
	int	player_x;
	int	player_y;

	player_x = (int)player->x_pos_map;
	player_y = (int)player->y_pos_map;
	if (map_data->map[player_y][player_x + 1] == '2')
		is_open(map_data, player_x + 1, player_y);
	else if (map_data->map[player_y][player_x - 1] == '2')
		is_open(map_data, player_x - 1, player_y);
	else if (map_data->map[player_y + 1][player_x] == '2')
		is_open(map_data, player_x, player_y + 1);
	else if (map_data->map[player_y - 1][player_x] == '2')
		is_open(map_data, player_x, player_y - 1);
}

void	animation(void *param)
{
	t_map_data	*map_data;
	static int	i = 0;

	map_data = param;
	if (i == 61)
	{
		i = 0;
		map_data->animation_playing = false;
		return ;
	}
	if (map_data->animation_playing)
	{
		mlx_delete_image(map_data->mlx, map_data->img_frame);
		map_data->text = mlx_load_png(map_data->frames[i]);
		map_data->img_frame = mlx_texture_to_image(map_data->mlx,
				map_data->text);
		mlx_image_to_window(map_data->mlx, map_data->img_frame, 730, 720);
		i++;
	}
}
