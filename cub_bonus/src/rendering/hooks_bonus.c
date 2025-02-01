/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:10 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/01 17:01:55 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static void	up_down(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_W))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map
				+ map_data->player->dir_x * speed)] != '1')
			map_data->player->x_pos_map += map_data->player->dir_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->dir_y
				* speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map += map_data->player->dir_y * speed;
	}
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_S))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map
				- map_data->player->dir_x * speed)] != '1')
			map_data->player->x_pos_map -= map_data->player->dir_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->dir_y
				* speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map -= map_data->player->dir_y * speed;
	}
}

static void	left_right(t_map_data *map_data, double speed)
{
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_A))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map
				- map_data->player->plane_x * speed)] != '1')
			map_data->player->x_pos_map -= map_data->player->plane_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				- map_data->player->plane_y
				* speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map -= map_data->player->plane_y * speed;
	}
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_D))
	{
		if (map_data->map[(int)map_data->player->y_pos_map][(int)(map_data->player->x_pos_map
				+ map_data->player->plane_x * speed)] != '1')
			map_data->player->x_pos_map += map_data->player->plane_x * speed;
		if (map_data->map[(int)(map_data->player->y_pos_map
				+ map_data->player->plane_y
				* speed)][(int)map_data->player->x_pos_map] != '1')
			map_data->player->y_pos_map += map_data->player->plane_y * speed;
	}
}

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

void	is_open(t_map_data *map_data, int player_x, int player_y)
{
	if (map_data->map[player_y][player_x] == 'D')
	{
		map_data->map[player_y][player_x] = '2';
		map_data->door->x = player_x;
		map_data->door->y = player_y;
		map_data->door->state = 1;
	}
	else if (map_data->map[player_y][player_x] == '2')
	{
		map_data->map[player_y][player_x] = 'D';
		map_data->door->x = player_x;
		map_data->door->y = player_y;
		map_data->door->state = 3;
	}
}

void	open_door(t_map_data *map_data, t_player *player)
{
	int	player_x;
	int	player_y;

	player_x = (int)player->x_pos_map;
	player_y = (int)player->y_pos_map;
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
	int	player_x;
	int	player_y;

	player_x = (int)player->x_pos_map;
	player_y = (int)player->y_pos_map;
	if (map_data->map[player_y][player_x + 1] == '2')
		is_open(map_data, player_x + 1, player_y);
	else if (map_data->map[player_y][player_x - 1] == '2')
		is_open(map_data, player_x - 1, player_y);
	else if (map_data->map[player_y + 1][player_x] == '2')
		is_open(map_data, player_x, player_y + 1);
	else if (map_data->map[player_y - 1][player_x] == '2')
		is_open(map_data, player_x, player_y - 1);
}

void	animation(void *param)
{
	t_map_data	*map_data;
	static int	i = 0;

	map_data = param;
	if (i == 61)
	{
		i = 0;
		map_data->animation_playing = false;
		return ;
	}
	if (map_data->animation_playing)
	{
		mlx_delete_image(map_data->mlx, map_data->img_frame);
		map_data->text = mlx_load_png(map_data->frames[i]);
		map_data->img_frame = mlx_texture_to_image(map_data->mlx,
				map_data->text);
		mlx_image_to_window(map_data->mlx, map_data->img_frame, 730, 720);
		i++;
	}
}

void	my_keyhook(void *param)
{
	t_map_data	*map_data;

	map_data = (t_map_data *)param;
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(map_data->mlx);
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_O))
		open_door(map_data, map_data->player);
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_C))
		close_door(map_data, map_data->player);
	if (mlx_is_key_down(map_data->mlx, MLX_KEY_SPACE))
		map_data->animation_playing = true;
	animation(map_data);
	up_down(map_data, map_data->speed);
	left_right(map_data, map_data->speed);
	rotation_left(map_data, map_data->player->rotation_speed);
	rotation_right(map_data, map_data->player->rotation_speed);
	raycasting(map_data);
	map_2d(map_data, -1);
}
