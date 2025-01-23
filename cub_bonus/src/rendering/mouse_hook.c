/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 02:07:37 by oel-feng          #+#    #+#             */
/*   Updated: 2025/01/23 16:02:33 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static void	mouse_rotation(t_map_data *map_data, double offset)
{
	double	rot_speed;
	double	olddir_x;
	double	oldplane_x;

	rot_speed = -offset * 0.003;
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

void	mouse_hook(double x_pos, double y_pos, void *param)
{
	static double	last_x = 0;
	static int		set_pos = 1;
	t_map_data		*map_data;
	double			offset;

	(void)y_pos;
	map_data = (t_map_data *)param;
	if (set_pos)
	{
		last_x = x_pos;
		set_pos = 0;
		return ;
	}
	offset = x_pos - last_x;
	mouse_rotation(map_data, offset);
	last_x = x_pos;
}

void	hook_change(struct mlx_key_data keydata, void *param)
{
	t_map_data	*map_data;
	static bool	mouse = false;

	(void)keydata;
	map_data = (t_map_data *)param;
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_M))
	{
		if (mouse == false)
			mlx_set_cursor_mode(map_data->mlx, MLX_MOUSE_NORMAL);
		else
			mlx_set_cursor_mode(map_data->mlx, MLX_MOUSE_DISABLED);
		mouse = !mouse;
	}
}
