/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:10 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/03 04:13:06 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static void	rotation_left(t_map_data *map_data, double rot_speed)
{
	double	olddir_x;
	double	oldplane_x;

	if (mlx_is_key_down(map_data->mlx, MLX_KEY_LEFT))
	{
		olddir_x = map_data->player->dir_x;
		map_data->player->dir_x = map_data->player->dir_x * cos(-rot_speed)
			- map_data->player->dir_y * sin(-rot_speed);
		map_data->player->dir_y = olddir_x * sin(-rot_speed)
			+ map_data->player->dir_y * cos(-rot_speed);
		oldplane_x = map_data->player->plane_x;
		map_data->player->plane_x = map_data->player->plane_x * cos(-rot_speed)
			- map_data->player->plane_y * sin(-rot_speed);
		map_data->player->plane_y = oldplane_x * sin(-rot_speed)
			+ map_data->player->plane_y * cos(-rot_speed);
	}
}

static void	rotation_right(t_map_data *map_data, double rot_speed)
{
	double	olddir_x;
	double	oldplane_x;

	if (mlx_is_key_down(map_data->mlx, MLX_KEY_RIGHT))
	{
		olddir_x = map_data->player->dir_x;
		map_data->player->dir_x = map_data->player->dir_x * cos(rot_speed)
			- map_data->player->dir_y * sin(rot_speed);
		map_data->player->dir_y = olddir_x * sin(rot_speed)
			+ map_data->player->dir_y * cos(rot_speed);
		oldplane_x = map_data->player->plane_x;
		map_data->player->plane_x = map_data->player->plane_x * cos(rot_speed)
			- map_data->player->plane_y * sin(rot_speed);
		map_data->player->plane_y = oldplane_x * sin(rot_speed)
			+ map_data->player->plane_y * cos(rot_speed);
	}
}

void	my_keyhook(void *param)
{
	t_map_data	*map_data;

	map_data = (t_map_data *)param;
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_ESCAPE))
		cleanup_and_exit(map_data);
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_O))
		open_door(map_data, map_data->player);
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_C))
		close_door(map_data, map_data->player);
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_SPACE))
		map_data->animation_playing = true;
	animation(map_data);
	up_mvmnt(map_data, map_data->speed);
	down_mvmnt(map_data, map_data->speed);
	left_mvmnt(map_data, map_data->speed);
	right_mvmnt(map_data, map_data->speed);
	rotation_left(map_data, map_data->player->rotation_speed);
	rotation_right(map_data, map_data->player->rotation_speed);
	raycasting(map_data);
	map_2d(map_data, -1);
}
