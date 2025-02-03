/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 03:37:01 by oel-feng          #+#    #+#             */
/*   Updated: 2025/02/03 03:40:43 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

void	up_mvmnt(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_W))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map
				+ map_data->player->dir_x * speed)] != '1'
				&& map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map
				+ map_data->player->dir_x * speed)] != 'D')
			map_data->player->x_pos_map += map_data->player->dir_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->dir_y * speed)]
				[(int)map_data->player->x_pos_map] != '1'
				&& map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->dir_y * speed)]
				[(int)map_data->player->x_pos_map] != 'D')
			map_data->player->y_pos_map += map_data->player->dir_y * speed;
	}
}

void	down_mvmnt(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_S))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map - map_data->player->dir_x
				* speed)] != '1'
				&& map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map - map_data->player->dir_x
				* speed)] != 'D')
			map_data->player->x_pos_map -= map_data->player->dir_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->dir_y * speed)]
				[(int)map_data->player->x_pos_map] != '1'
				&& map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->dir_y * speed)]
				[(int)map_data->player->x_pos_map] != 'D')
			map_data->player->y_pos_map -= map_data->player->dir_y * speed;
	}
}

void	left_mvmnt(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_A))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map
				- map_data->player->plane_x * speed)] != '1'
				&& map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map
				- map_data->player->plane_x * speed)] != 'D')
			map_data->player->x_pos_map -= map_data->player->plane_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->plane_y * speed)]
				[(int)map_data->player->x_pos_map] != '1'
				&& map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->plane_y * speed)]
				[(int)map_data->player->x_pos_map] != 'D')
			map_data->player->y_pos_map -= map_data->player->plane_y * speed;
	}
}

void	right_mvmnt(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_D))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map + map_data->player->plane_x
				* speed)] != '1'
				&& map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map + map_data->player->plane_x
				* speed)] != 'D')
			map_data->player->x_pos_map += map_data->player->plane_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->plane_y * speed)]
				[(int)map_data->player->x_pos_map] != '1'
				&& map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->plane_y * speed)]
				[(int)map_data->player->x_pos_map] != 'D')
			map_data->player->y_pos_map += map_data->player->plane_y * speed;
	}
}
