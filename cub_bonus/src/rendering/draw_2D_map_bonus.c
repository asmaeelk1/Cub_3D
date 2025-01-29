/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2D_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghriyba <ghriyba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:49:21 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/28 20:20:49 by ghriyba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static void	draw_square(t_map_data *data, int x, int y, long color)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = 0;
	start_x = x;
	start_y = y;
	while (i < 15)
	{
		j = 0;
		while (j < 15)
		{
			if (start_x + i < 200 && start_y + j < 200
				&& start_x + i > 0 && start_y + j > 0)
				mlx_put_pixel(data->mini_map, start_x + i, start_y + j, color);
			j++;
		}
		i++;
	}
}

static void	draw_player(t_map_data *map_data, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (i < 200 && j < 200)
				mlx_put_pixel(map_data->mini_map, 200 / 2 + j,
					200 / 2 + i, color);
			j++;
		}
		i++;
	}
}

static void	map_background(t_map_data *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			mlx_put_pixel((map_data->mini_map), i, j, 0X000000FF);
			j++;
		}
		i++;
	}
}

void	map_2d(t_map_data *map_data, int i)
{
	int	x;
	int	y;
	int	j;
	int	off_x;
	int	off_y;

	off_x = (200 / 2) - ((map_data->player->x_pos_map) * 15);
	off_y = (200 / 2) - ((map_data->player->y_pos_map) * 15);
	map_background(map_data);
	while (map_data->map[++i])
	{
		j = -1;
		while (map_data && map_data->map[i][++j])
		{
			x = (j * 15) + off_x;
			y = (i * 15) + off_y;
			if (map_data->map[i][j] == '1')
				draw_square(map_data, x, y, 255);
			else if (map_data->map[i][j] == '0' || map_data->map[i][j] == '2')
				draw_square(map_data, x, y, 0X6B01C8FF);
		}
	}
	draw_player(map_data, 77657578);
}
