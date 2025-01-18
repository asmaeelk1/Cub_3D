/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:10 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/18 22:30:17 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

// void	hook_vector(t_map_data *data)
// {
// 	float	value;

// 	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_RIGHT))
// 	{
// 		data->player->turn_dir = 1;
// 		value = data->player->turn_dir * data->player->rotation_speed;
// 		data->player->rotate_angle += value;
// 	}
// 	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_LEFT))
// 	{
// 		data->player->turn_dir = -1;
// 		value = data->player->turn_dir * data->player->rotation_speed;
// 		data->player->rotate_angle += value;
// 	}
// }

void	my_keyhook(void *param)
{
	t_map_data	*map_data;
	double		speed;
	double		rot_speed;
	double		oldDirX;
	double		oldPlaneX;
	

	map_data = (t_map_data *)param;
	speed = map_data->speed;
	rot_speed = map_data->player->rotation_speed;
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map_data->data_mlx->mlx);
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_W))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map + map_data->player->dirX * speed)] != '1')
			map_data->player->x_pos_map += map_data->player->dirX * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map + map_data->player->dirY * speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map += map_data->player->dirY * speed;
	}
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_S))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map - map_data->player->dirX * speed)] != '1')
			map_data->player->x_pos_map -= map_data->player->dirX * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map - map_data->player->dirY * speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map -= map_data->player->dirY * speed;
	}
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_A))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map - map_data->player->planeX * speed)] != '1')
			map_data->player->x_pos_map -= map_data->player->planeX * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map - map_data->player->planeY * speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map -= map_data->player->planeY * speed;
	}
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_D))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map + map_data->player->planeX * speed)] != '1')
			map_data->player->x_pos_map += map_data->player->planeX * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map + map_data->player->planeY * speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map += map_data->player->planeY * speed;
	}
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_LEFT))
	{
		oldDirX = map_data->player->dirX;
		map_data->player->dirX = map_data->player->dirX * cos(-rot_speed) - map_data->player->dirY * sin(-rot_speed);
		map_data->player->dirY = oldDirX * sin(-rot_speed) + map_data->player->dirY * cos(-rot_speed);
		oldPlaneX = map_data->player->planeX;
		map_data->player->planeX = map_data->player->planeX * cos(-rot_speed) - map_data->player->planeY * sin(-rot_speed);
		map_data->player->planeY = oldPlaneX * sin(-rot_speed) + map_data->player->planeY * cos(-rot_speed);
	}
	if (mlx_is_key_down(map_data->data_mlx->mlx, MLX_KEY_RIGHT))
	{
		oldDirX = map_data->player->dirX;
		map_data->player->dirX = map_data->player->dirX * cos(rot_speed) - map_data->player->dirY * sin(rot_speed);
		map_data->player->dirY = oldDirX * sin(rot_speed) + map_data->player->dirY * cos(rot_speed);
		oldPlaneX = map_data->player->planeX;
		map_data->player->planeX = map_data->player->planeX * cos(rot_speed) - map_data->player->planeY * sin(rot_speed);
		map_data->player->planeY = oldPlaneX * sin(rot_speed) + map_data->player->planeY * cos(rot_speed);	
	}
	raycasting(map_data);
}
