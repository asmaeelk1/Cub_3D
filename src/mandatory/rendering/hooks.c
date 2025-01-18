/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:10 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/18 16:57:52 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void	hook_vector(t_map_data *data)
{
	float	value;

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

void	my_keyhook(void *param)
{
	t_map_data	**data;

	data = param;
	if (mlx_is_key_down((*data)->data_mlx->mlx, MLX_KEY_ESCAPE))
		mlx_close_window((*data)->data_mlx->mlx);
	hook_vector(*data);
	mlx_delete_image((*data)->data_mlx->mlx, (*data)->data_mlx->image);
	(*data)->data_mlx->image = mlx_new_image((*data)->data_mlx->mlx, WIDTH, H);
	start_moves(*data);
	start_raycast(data);
	mlx_image_to_window((*data)->data_mlx->mlx, (*data)->data_mlx->image, 0, 0);
}
