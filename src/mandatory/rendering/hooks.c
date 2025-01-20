/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:10 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/20 01:22:36 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static void	up_down(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_W))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map
				+ map_data->player->dir_x * speed)] != '1')
			map_data->player->x_pos_map += map_data->player->dir_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->dir_y * speed)]
				[(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map += map_data->player->dir_y * speed;
	}
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_S))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map - map_data->player->dir_x
				* speed)] != '1')
			map_data->player->x_pos_map -= map_data->player->dir_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->dir_y * speed)]
				[(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map -= map_data->player->dir_y * speed;
	}
}

static void	left_right(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_A))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map
				- map_data->player->plane_x * speed)] != '1')
			map_data->player->x_pos_map -= map_data->player->plane_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->plane_y * speed)]
				[(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map -= map_data->player->plane_y * speed;
	}
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_D))
	{
		if (map_data->map[(int)map_data->player->y_pos_map]
			[(int)(map_data->player->x_pos_map + map_data->player->plane_x
				* speed)] != '1')
			map_data->player->x_pos_map += map_data->player->plane_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->plane_y * speed)]
				[(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map += map_data->player->plane_y * speed;
	}
}

static void	rotation_left(t_map_data *map_data, double rot_speed)
{
	double		olddir_x;
	double		oldplane_x;

	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_LEFT))
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
	double		olddir_x;
	double		oldplane_x;

	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_RIGHT))
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
	double		speed;
	double		rot_speed;

	map_data = (t_map_data *)param;
	speed = map_data->speed;
	rot_speed = map_data->player->rotation_speed;
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map_data->data_mlx->mlx);
	up_down(map_data, speed);
	left_right(map_data, speed);
	rotation_left(map_data, rot_speed);
	rotation_right(map_data, rot_speed);
	raycasting(map_data);
}
