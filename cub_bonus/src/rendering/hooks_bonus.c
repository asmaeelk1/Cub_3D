/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghriyba <ghriyba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:10 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/29 23:10:54 by ghriyba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static void	up_down(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_W))
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
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_S))
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
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_A))
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
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_D))
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
	double		olddir_x;
	double		oldplane_x;

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

// void	movement_shake(t_player *player)
// {
// 		static float shake_time = 0;
//     	static float shake_intensity = 0.03;
// 		shake_time += 0.09;
// 		float shake_x = sin(shake_time * 8) * shake_intensity;
//         float shake_y = cos(shake_time * 8) * shake_intensity;
//     	player->y_pos_map += shake_y;
//         player->x_pos_map += shake_x;
// }

void is_open(t_map_data *map_data, int player_x, int player_y) {
    if (map_data->map[player_y][player_x] == 'D') {
        map_data->map[player_y][player_x] = '2';
    } else if (map_data->map[player_y][player_x] == '2') {
        map_data->map[player_y][player_x] = 'D';
    }
}

void	open_door(t_map_data *map_data, t_player *player) 
{
	int player_x = (int)player->x_pos_map;
    int player_y = (int)player->y_pos_map;

    if (map_data->map[player_y][player_x + 1] == 'D')
        is_open(map_data, player_x + 1, player_y);
    else if (map_data->map[player_y][player_x - 1] == 'D')
        is_open(map_data, player_x - 1, player_y);
    else if (map_data->map[player_y + 1][player_x] == 'D')
        is_open(map_data, player_x, player_y + 1);
    else if (map_data->map[player_y - 1][player_x] == 'D')
        is_open(map_data, player_x, player_y - 1);
}

void	close_door(t_map_data *map_data, t_player *player)
{
	int player_x = (int)player->x_pos_map;
    int player_y = (int)player->y_pos_map;

    if (map_data->map[player_y][player_x + 1] == '2')
        is_open(map_data, player_x + 1, player_y);
    else if (map_data->map[player_y][player_x - 1] == '2')
        is_open(map_data, player_x - 1, player_y);
    else if (map_data->map[player_y + 1][player_x] == '2')
        is_open(map_data, player_x, player_y + 1);
    else if (map_data->map[player_y - 1][player_x] == '2')
        is_open(map_data, player_x, player_y - 1);
}

void my_keyhook(void *param)
{
    t_map_data *map_data ;

	map_data = (t_map_data *)param;
    if (mlx_is_key_down(map_data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(map_data->mlx);
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_O))
		open_door(map_data, map_data->player);
	if( mlx_is_key_down(map_data->mlx, MLX_KEY_C))
		close_door(map_data, map_data->player);
    up_down(map_data, map_data->speed);
    left_right(map_data, map_data->speed);
    rotation_left(map_data, map_data->player->rotation_speed);
    rotation_right(map_data, map_data->player->rotation_speed);
    raycasting(map_data);
    map_2d(map_data, -1);
}
