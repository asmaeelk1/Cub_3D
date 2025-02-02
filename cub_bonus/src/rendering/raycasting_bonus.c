/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:35:38 by oel-feng          #+#    #+#             */
/*   Updated: 2025/02/02 21:38:56 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static void	ray_cont(t_cast *cast, t_map_data *map_data)
{
	if (cast->side == 0)
		cast->perpwalldist = (cast->map_x - map_data->player->x_pos_map + (1
					- cast->step_x) / 2) / cast->raydir_x;
	else
		cast->perpwalldist = (cast->map_y - map_data->player->y_pos_map + (1
					- cast->step_y) / 2) / cast->raydir_y;
	if (cast->perpwalldist < 0.1)
		cast->perpwalldist = 0.1;
	cast->lineheight = (int)(HEIGHT / cast->perpwalldist);
	if (cast->lineheight > HEIGHT * 10)
		cast->lineheight = HEIGHT * 10;
	cast->drawstart = -cast->lineheight / 2 + HEIGHT / 2;
	cast->drawend = cast->lineheight / 2 + HEIGHT / 2;
	if (cast->drawstart < 0)
		cast->drawstart = 0;
	if (cast->drawend >= HEIGHT)
		cast->drawend = HEIGHT - 1;
	if (cast->side == 0)
		cast->wall_x = map_data->player->y_pos_map + cast->perpwalldist
			* cast->raydir_y;
	else
		cast->wall_x = map_data->player->x_pos_map + cast->perpwalldist
			* cast->raydir_x;
}

static void	set_dda(t_cast *cast, t_map_data *map_data)
{
	while (cast->hit == 0)
	{
		if (cast->sidedist_x < cast->sidedist_y)
		{
			cast->sidedist_x += cast->deltadist_x;
			cast->map_x += cast->step_x;
			cast->side = 0;
		}
		else
		{
			cast->sidedist_y += cast->deltadist_y;
			cast->map_y += cast->step_y;
			cast->side = 1;
		}
		if (cast->map_x < 0 || cast->map_x >= WIDTH || cast->map_y < 0
			|| cast->map_y >= HEIGHT)
			break ;
		if (map_data->map[cast->map_y][cast->map_x] == '1'
			|| map_data->map[cast->map_y][cast->map_x] == 'D')
			cast->hit = 1;
	}
}

static void	init_step(t_cast *cast, t_map_data *map_data)
{
	if (cast->raydir_x < 0)
	{
		cast->step_x = -1;
		cast->sidedist_x = (map_data->player->x_pos_map - cast->map_x)
			* cast->deltadist_x;
	}
	else
	{
		cast->step_x = 1;
		cast->sidedist_x = (cast->map_x + 1.0 - map_data->player->x_pos_map)
			* cast->deltadist_x;
	}
	if (cast->raydir_y < 0)
	{
		cast->step_y = -1;
		cast->sidedist_y = (map_data->player->y_pos_map - cast->map_y)
			* cast->deltadist_y;
	}
	else
	{
		cast->step_y = 1;
		cast->sidedist_y = (cast->map_y + 1.0 - map_data->player->y_pos_map)
			* cast->deltadist_y;
	}
}

static void	init_data(t_cast *cast, t_map_data *map_data, int x)
{
	cast->camera_x = 2 * x / (double)WIDTH - 1;
	cast->raydir_x = map_data->player->dir_x + map_data->player->plane_x
		* cast->camera_x;
	cast->raydir_y = map_data->player->dir_y + map_data->player->plane_y
		* cast->camera_x;
	cast->map_x = map_data->player->x_pos_map;
	cast->map_y = map_data->player->y_pos_map;
	if (cast->raydir_x == 0)
		cast->deltadist_x = 1e30;
	else
		cast->deltadist_x = fabs(1 / cast->raydir_x);
	if (cast->raydir_y == 0)
		cast->deltadist_y = 1e30;
	else
		cast->deltadist_y = fabs(1 / cast->raydir_y);
	cast->hit = 0;
}

void	raycasting(t_map_data *map_data)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		init_data(&map_data->cast, map_data, x);
		init_step(&map_data->cast, map_data);
		set_dda(&map_data->cast, map_data);
		ray_cont(&map_data->cast, map_data);
		set_textures_data(&map_data->cast, map_data, x, -1);
	}
}
