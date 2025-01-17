/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_hooks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 03:28:15 by wabolles          #+#    #+#             */
/*   Updated: 2025/01/17 05:46:52 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	rotation_hook(t_map_data *data)
{
	double	value;

	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_RIGHT))
	{
		data->player->turn_dir = 1;
		value = data->player->turn_dir * data->player->rotation_speed;
		data->player->rotate_angle += value;
	}
	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_LEFT))
	{
		data->player->turn_dir = -1;
		value = data->player->turn_dir * data->player->rotation_speed;
		data->player->rotate_angle += value;
	}
}

void	translation_hook2(t_map_data *data, double pos_x, double pos_y, double mv)
{
	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_D))
	{
		pos_x = mv * cos(data->player->rotate_angle + M_PI_2);
		pos_y = mv * sin(data->player->rotate_angle + M_PI_2);
	}
	if (!is_wall(&data, data->player->xc + pos_x, data->player->yc + pos_y))
	{
		data->p_x_pos += pos_x;
		data->p_y_pos += pos_y;
	}
}

void	translation_hook(t_map_data *data)
{
	double	pos_x;
	double	pos_y;
	double	movement_speed;

	pos_x = 0;
	pos_y = 0;
	movement_speed = 3;
	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_W))
	{
		pos_y = movement_speed * sin(data->player->rotate_angle);
		pos_x = movement_speed * cos(data->player->rotate_angle);
	}
	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_A))
	{
		pos_x = -movement_speed * cos(data->player->rotate_angle + M_PI_2);
		pos_y = -movement_speed * sin(data->player->rotate_angle + M_PI_2);
	}
	if (mlx_is_key_down(data->data_mlx->mlx, MLX_KEY_S))
	{
		pos_y = -movement_speed * sin(data->player->rotate_angle);
		pos_x = -movement_speed * cos(data->player->rotate_angle);
	}
	translation_hook2(data, pos_x, pos_y, movement_speed);
}

void	my_keyhook(void *param)
{
	t_map_data	**data;

	data = param;
	if (mlx_is_key_down((*data)->data_mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window((*data)->data_mlx->mlx);
	translation_hook(*data);
	rotation_hook(*data);
	mlx_delete_image((*data)->data_mlx->mlx, (*data)->data_mlx->image);
	(*data)->data_mlx->image = mlx_new_image((*data)->data_mlx->mlx, WIDTH, H);
	map_2d(data);
	mlx_image_to_window((*data)->data_mlx->mlx, (*data)->data_mlx->image, 0, 0);
}
