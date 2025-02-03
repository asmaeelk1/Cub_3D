/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_init_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 00:56:50 by oel-feng          #+#    #+#             */
/*   Updated: 2025/02/03 20:11:28 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static void	plane_rot(t_map_data *map_data)
{
	if (map_data->player->player == 'E')
	{
		map_data->player->dir_x = 1;
		map_data->player->dir_y = 0;
		map_data->player->plane_x = 0;
		map_data->player->plane_y = 0.66;
	}
	else if (map_data->player->player == 'W')
	{
		map_data->player->dir_x = -1;
		map_data->player->dir_y = 0;
		map_data->player->plane_x = 0;
		map_data->player->plane_y = -0.66;
	}
}

void	set_plane_rotation(t_map_data *map_data)
{
	map_data->speed = 0.1;
	map_data->player->rotation_speed = 0.05;
	if (map_data->player->player == 'N')
	{
		map_data->player->dir_x = 0;
		map_data->player->dir_y = -1;
		map_data->player->plane_x = 0.66;
		map_data->player->plane_y = 0;
	}
	else if (map_data->player->player == 'S')
	{
		map_data->player->dir_x = 0;
		map_data->player->dir_y = 1;
		map_data->player->plane_x = -0.66;
		map_data->player->plane_y = 0;
	}
	else
		plane_rot(map_data);
}
