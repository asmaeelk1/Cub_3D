/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:35:38 by oel-feng          #+#    #+#             */
/*   Updated: 2025/01/18 17:45:10 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

// ⣿⣿⣿⣿⣿⣿⠿⢋⣥⣴⣶⣶⣶⣬⣙⠻⠟⣋⣭⣭⣭⣭⡙⠻⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⡿⢋⣴⣿⣿⠿⢟⣛⣛⣛⠿⢷⡹⣿⣿⣿⣿⣿⣿⣆⠹⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⡿⢁⣾⣿⣿⣴⣿⣿⣿⣿⠿⠿⠷⠥⠱⣶⣶⣶⣶⡶⠮⠤⣌⡙⢿⣿⣿ //
// ⣿⡿⢛⡁⣾⣿⣿⣿⡿⢟⡫⢕⣪⡭⠥⢭⣭⣉⡂⣉⡒⣤⡭⡉⠩⣥⣰⠂⠹⣿ //
// ⡟⢠⣿⣱⣿⣿⣿⣏⣛⢲⣾⣿⠃⠄⠐⠈⣿⣿⣿⣿⣿⣿⠄⠁⠃⢸⣿⣿⡧⣿ //
// ⢠⣿⣿⣿⣿⣿⣿⣿⣿⣇⣊⠙⠳⠤⠤⠾⣟⠛⠍⣹⣛⣛⣢⣀⣠⣛⡯⢉⣰⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡶⠶⢒⣠⣼⣿⣿⣛⠻⠛⢛⣛⠉⣴⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡿⢛⡛⢿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡈⢿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⠸⣿⡻⢷⣍⣛⠻⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢇⡘⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣷⣝⠻⠶⣬⣍⣛⣛⠓⠶⠶⠶⠤⠬⠭⠤⠶⠶⠞⠛⣡⣿⣿ //
// ⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣬⣭⣍⣙⣛⣛⣛⠛⠛⠛⠿⠿⠿⠛⣠⣿⣿⣿ //
// ⣦⣈⠉⢛⠻⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⣁⣴⣾⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣶⣮⣭⣁⣒⣒⣒⠂⠠⠬⠭⠭⠭⢀⣀⣠⣄⡘⠿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡈⢿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣉⡥⠶⢶⣿⣿⣿⣿⣷⣆⠉⠛⠿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡿⢡⡞⠁⠀⠀⠤⠈⠿⠿⠿⠿⣿⠀⢻⣦⡈⠻⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡇⠘⡁⠀⢀⣀⣀⣀⣈⣁⣐⡒⠢⢤⡈⠛⢿⡄⠻⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡇⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⠉⠐⠄⡈⢀⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⠇⢠⣿⣿⣿⣿⡿⢿⣿⣿⣿⠁⢈⣿⡄⠀⢀⣀⠸⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⡿⠟⣡⣶⣶⣬⣭⣥⣴⠀⣾⣿⣿⣿⣶⣾⣿⣧⠀⣼⣿⣷⣌⡻⢿⣿ //
// ⣿⣿⠟⣋⣴⣾⣿⣿⣿⣿⣿⣿⣿⡇⢿⣿⣿⣿⣿⣿⣿⡿⢸⣿⣿⣿⣿⣷⠄⢻ //
// ⡏⠰⢾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⢂⣭⣿⣿⣿⣿⣿⠇⠘⠛⠛⢉⣉⣠⣴⣾ //
// ⣿⣷⣦⣬⣍⣉⣉⣛⣛⣉⠉⣤⣶⣾⣿⣿⣿⣿⣿⣿⡿⢰⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡘⣿⣿⣿⣿⣿⣿⣿⣿⡇⣼⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⢸⣿⣿⣿⣿⣿⣿⣿⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿ //

bool	check_collision(t_map_data *map_data, double new_x, double new_y)
{
	double buffer;
	int map_x;
	int map_y;

	buffer = 0.2;
	map_x = (int)new_x;
	map_y = (int)new_y;
	// printf("Checking collision: new_x=%f, new_y=%f, map_x=%d, map_y=%d\n", 
	//        new_x, new_y, map_x, map_y);
	// printf("Map value at position: %c\n", map_data->map[map_y][map_x]);
	// printf("Buffer checks: left=%f right=%f top=%f bottom=%f\n",
	//        new_x - map_x, map_x + 1 - new_x, new_y - map_y, map_y + 1 - new_y);
	
	if (new_x - map_x < buffer && map_data->map[map_y][map_x-1] == '1')
		return (true);
	if (map_x + 1 - new_x < buffer && map_data->map[map_y][map_x+1] == '1')
		return (true);
	if (new_y - map_y < buffer && map_data->map[map_y-1][map_x] == '1')
		return (true);
	if (map_y + 1 - new_y < buffer && map_data->map[map_y+1][map_x] == '1')
		return (true);
	return (false);
}

void movement_hook(mlx_key_data_t keydata, void* data)
{
	t_map_data*	map_data;
	
	map_data = (t_map_data*)data;
	if (keydata.action == MLX_PRESS)
	{
		if (keydata.key == MLX_KEY_W)
			map_data->keys.w_pressed = true;
		if (keydata.key == MLX_KEY_S)
			map_data->keys.s_pressed = true;
		if (keydata.key == MLX_KEY_A)
			map_data->keys.a_pressed = true;
		if (keydata.key == MLX_KEY_D)
			map_data->keys.d_pressed = true;
		if (keydata.key == MLX_KEY_LEFT)
			map_data->keys.left_pressed = true;
		if (keydata.key == MLX_KEY_RIGHT)
			map_data->keys.right_pressed = true;
	}
	if (keydata.action == MLX_RELEASE)
	{
		if (keydata.key == MLX_KEY_W)
			map_data->keys.w_pressed = false;
		if (keydata.key == MLX_KEY_S)
			map_data->keys.s_pressed = false;
		if (keydata.key == MLX_KEY_A)
			map_data->keys.a_pressed = false;
		if (keydata.key == MLX_KEY_D)
			map_data->keys.d_pressed = false;
		if (keydata.key == MLX_KEY_LEFT)
			map_data->keys.left_pressed = false;
		if (keydata.key == MLX_KEY_RIGHT)
			map_data->keys.right_pressed = false;
	}
}


void start_moves(t_map_data *map_data)
{
	double	speed;
	double	rot_speed;
	double	new_x;
	double	new_y;
	double	oldDirX;
	double	oldPlaneX;

	printf("Current position: x=%d, y=%d\n", map_data->player->x_pos_map, map_data->player->y_pos_map);
	printf("Key states: W=%d, S=%d, A=%d, D=%d\n", map_data->keys.w_pressed, map_data->keys.s_pressed, map_data->keys.a_pressed, map_data->keys.d_pressed);
	printf("Initial player pos: x=%d, y=%d\n", map_data->player->x_pos_map, map_data->player->y_pos_map);
	printf("Initial player dir: x=%f, y=%f\n", map_data->player->dirX, map_data->player->dirY);
	printf("Initial player plane: x=%f, y=%f\n", map_data->player->planeX, map_data->player->planeY);
	speed = map_data->speed;
	rot_speed = map_data->player->rotation_speed;
	if (map_data->keys.w_pressed)
	{
		new_x = map_data->player->x_pos_map + map_data->player->dirX * speed;
		new_y = map_data->player->y_pos_map + map_data->player->dirY * speed;
		printf("W pressed: Attempting to move to x=%f, y=%f (dir=%f,%f)\n", 
		   new_x, new_y, map_data->player->dirX, map_data->player->dirY);
		if (!check_collision(map_data, new_x, map_data->player->y_pos_map))
		{
			printf("X movement allowed\n");
			map_data->player->x_pos_map = new_x;
		}
		if (!check_collision(map_data, map_data->player->x_pos_map, new_y))
		{
			printf("Y movement allowed\n");
			map_data->player->y_pos_map = new_y;
		}	
	}
	if (map_data->keys.s_pressed)
	{
		new_x = map_data->player->x_pos_map - map_data->player->dirX * speed;
		new_y = map_data->player->y_pos_map - map_data->player->dirY * speed;
		printf("S pressed: Attempting to move to x=%f, y=%f (dir=%f,%f)\n", 
		   new_x, new_y, map_data->player->dirX, map_data->player->dirY);
		if (!check_collision(map_data, new_x, map_data->player->y_pos_map))
		{
			printf("X movement allowed\n");
			map_data->player->x_pos_map = new_x;
		}
		if (!check_collision(map_data, map_data->player->x_pos_map, new_y))
		{
			printf("Y movement allowed\n");
			map_data->player->y_pos_map = new_y;
		}
	}
	if (map_data->keys.a_pressed)
	{
		new_x = map_data->player->x_pos_map - map_data->player->planeX * speed;
		new_y = map_data->player->y_pos_map - map_data->player->planeY * speed;
		if (!check_collision(map_data, new_x, map_data->player->y_pos_map))
			map_data->player->x_pos_map = new_x;
		if (!check_collision(map_data, map_data->player->x_pos_map, new_y))
			map_data->player->y_pos_map = new_y;
	}
	if (map_data->keys.d_pressed)
	{
		new_x = map_data->player->x_pos_map + map_data->player->planeX * speed;
		new_y = map_data->player->y_pos_map + map_data->player->planeY * speed;
		if (!check_collision(map_data, new_x, map_data->player->y_pos_map))
			map_data->player->x_pos_map = new_x;
		if (!check_collision(map_data, map_data->player->x_pos_map, new_y))
			map_data->player->y_pos_map = new_y;
	}
	if (map_data->keys.right_pressed)
	{
		oldDirX = map_data->player->dirX;
		map_data->player->dirX = map_data->player->dirX * cos(-rot_speed) - map_data->player->dirY * sin(-rot_speed);
		map_data->player->dirY = oldDirX * sin(-rot_speed) + map_data->player->dirY * cos(-rot_speed);
		oldPlaneX = map_data->player->planeX;
		map_data->player->planeX = map_data->player->planeX * cos(-rot_speed) - map_data->player->planeY * sin(-rot_speed);
		map_data->player->planeY = oldPlaneX * sin(-rot_speed) + map_data->player->planeY * cos(-rot_speed);
	}
	if (map_data->keys.left_pressed)
	{
		oldDirX = map_data->player->dirX;
		map_data->player->dirX = map_data->player->dirX * cos(rot_speed) - map_data->player->dirY * sin(rot_speed);
		map_data->player->dirY = oldDirX * sin(rot_speed) + map_data->player->dirY * cos(rot_speed);
		oldPlaneX = map_data->player->planeX;
		map_data->player->planeX = map_data->player->planeX * cos(rot_speed) - map_data->player->planeY * sin(rot_speed);
		map_data->player->planeY = oldPlaneX * sin(rot_speed) + map_data->player->planeY * cos(rot_speed);
	}
}

void	recheck_text(t_map_data **map_data)
{
	int i;

	// if (!(*map_data)->textures)
	//     (*map_data)->textures = gcollector(sizeof(mlx_texture_t*) * 4, 1);
	if ((*map_data)->arr_text)
	{
		i = -1;
		while (++i < 4)
			free((*map_data)->arr_text[i]);
		free((*map_data)->arr_text);
	}
	(*map_data)->arr_text = malloc((*map_data)->data_mlx->width * sizeof(int *));
	i = -1;
	while (++i < (*map_data)->data_mlx->width)
		(*map_data)->arr_text[i] = malloc((*map_data)->data_mlx->height * sizeof(int));
}

void load_textures(t_map_data *map_data)
{
	map_data->textures[0] = mlx_load_png("./textures/test.png");
	map_data->textures[1] = mlx_load_png("./textures/test.png");
	map_data->textures[2] = mlx_load_png("./textures/test.png");
	map_data->textures[3] = mlx_load_png("./textures/test.png");
	if (!map_data->textures[0] || !map_data->textures[1] || !map_data->textures[2] || !map_data->textures[3])
		ft_err("Error: Failed to load textures");
	map_data->tex_width = map_data->textures[0]->width;
	map_data->tex_height = map_data->textures[0]->height;
}

void start_raycast(t_map_data **map_data)
{
	t_cast	cast;
	static int begin = 1;

	if (begin)
	{
		begin = 0;
		recheck_text(map_data);
		load_textures(*map_data);
	}
	if (!map_data || !*map_data || !(*map_data)->data_mlx)
	{
		printf("Invalid map_data in start_raycast\n");
		return;
	}
	cast = (*map_data)->cast;
	// recheck_text(map_data);
	raycasting_init(&cast);
	// load_textures(*map_data);
	// raycasting_init(&cast);
	raycasting(map_data, &cast);
}

void raycasting_init(t_cast *cast)
{
	cast->cameraX = 0;
	cast->rayDirX = 0;
	cast->rayDirY = 0;
	cast->mapX = 0;
	cast->mapY = 0;
	cast->sideDistX = 0;
	cast->sideDistY = 0;
	cast->deltaDistX = 0;
	cast->deltaDistY = 0;
	cast->perpWallDist = 0;
	cast->posX = 0;
	cast->stepX = 0;
	cast->stepY = 0;
	cast->hit = 0;
	cast->side = 0;
	cast->lineHeight = 0;
	cast->drawStart = 0;
	cast->drawEnd = 0;
}

void raycasting(t_map_data **map_data, t_cast *cast)
{
	if (!map_data || !*map_data || !(*map_data)->data_mlx || !(*map_data)->data_mlx->image)
	{
		printf("Error: Invalid pointers in raycasting\n");
		return;
	}
	const int width = (*map_data)->data_mlx->image->width;
	const int height = (*map_data)->data_mlx->image->height;
	uint32_t* pixels = (uint32_t*)(*map_data)->data_mlx->image->pixels;

	for (int x = 0; x < width; x++)
	{
		cast->cameraX = 2 * x / (double)width - 1;
		cast->rayDirX = (*map_data)->player->dirX + (*map_data)->player->planeX * cast->cameraX;
		cast->rayDirY = (*map_data)->player->dirY + (*map_data)->player->planeY * cast->cameraX;
		cast->mapX = (int)(*map_data)->player->x_pos_map;
		cast->mapY = (int)(*map_data)->player->y_pos_map;
		cast->deltaDistX = (cast->rayDirX == 0) ? 1e30 : fabs(1 / cast->rayDirX);
		cast->deltaDistY = (cast->rayDirY == 0) ? 1e30 : fabs(1 / cast->rayDirY);
		if (cast->rayDirX < 0)
		{
			cast->stepX = -1;
			cast->sideDistX = ((*map_data)->player->x_pos_map - cast->mapX) * cast->deltaDistX;
		}
		else
		{
			cast->stepX = 1;
			cast->sideDistX = (cast->mapX + 1.0 - (*map_data)->player->x_pos_map) * cast->deltaDistX;
		}
		if (cast->rayDirY < 0)
		{
			cast->stepY = -1;
			cast->sideDistY = ((*map_data)->player->y_pos_map - cast->mapY) * cast->deltaDistY;
		}
		else
		{
			cast->stepY = 1;
			cast->sideDistY = (cast->mapY + 1.0 - (*map_data)->player->y_pos_map) * cast->deltaDistY;
		}
		cast->hit = 0;
		while (cast->hit == 0)
		{
			if (cast->sideDistX < cast->sideDistY)
			{
				cast->sideDistX += cast->deltaDistX;
				cast->mapX += cast->stepX;
				cast->side = 0;
			}
			else
			{
				cast->sideDistY += cast->deltaDistY;
				cast->mapY += cast->stepY;
				cast->side = 1;
			}
			if (cast->mapX < 0 || cast->mapX >= (*map_data)->width_map || 
				cast->mapY < 0 || cast->mapY >= (*map_data)->height_map)
				break;
			if ((*map_data)->map[cast->mapY][cast->mapX] == '1')
				cast->hit = 1;
		}
		if (cast->side == 0)
			cast->perpWallDist = (cast->mapX - (*map_data)->player->x_pos_map + 
							   (1 - cast->stepX) / 2) / cast->rayDirX;
		else
			cast->perpWallDist = (cast->mapY - (*map_data)->player->y_pos_map + 
							   (1 - cast->stepY) / 2) / cast->rayDirY;
		if (cast->perpWallDist < 0.1)
			cast->perpWallDist = 0.1;
		cast->lineHeight = (int)(height / cast->perpWallDist);
		if (cast->lineHeight > height * 10)
			cast->lineHeight = height * 10;
		cast->drawStart = -cast->lineHeight / 2 + height / 2;
		cast->drawEnd = cast->lineHeight / 2 + height / 2;
		if (cast->drawStart < 0) cast->drawStart = 0;
		if (cast->drawEnd >= height) cast->drawEnd = height - 1;
		if (cast->side == 0)
			cast->wallX = (*map_data)->player->y_pos_map + cast->perpWallDist * cast->rayDirY;
		else
			cast->wallX = (*map_data)->player->x_pos_map + cast->perpWallDist * cast->rayDirX;
		cast->wallX -= floor(cast->wallX);
		cast->texX = (int)(cast->wallX * (*map_data)->tex_width);
		if (cast->side == 0 && cast->rayDirX > 0)
			cast->texX = (*map_data)->tex_width - cast->texX - 1;
		if (cast->side == 1 && cast->rayDirY < 0)
			cast->texX = (*map_data)->tex_width - cast->texX - 1;
		cast->step = (double)(*map_data)->tex_height / cast->lineHeight;
		cast->texPos = (cast->drawStart - height / 2 + cast->lineHeight / 2) * cast->step;

	   	for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			if (index < 0 || index >= width * height)
				continue;
			if (y < cast->drawStart)
				pixels[index] = (*map_data)->colors->c_ceiling;
			else if (y < cast->drawEnd)
			{
				cast->texY = (int)cast->texPos & ((*map_data)->tex_height - 1);
				cast->texPos += cast->step;
				cast->texNum = 0;
				if (cast->side == 0)
					cast->texNum = cast->rayDirX > 0 ? 0 : 1;
				else
					cast->texNum = cast->rayDirY > 0 ? 2 : 3;
				uint8_t *texPixel = &(*map_data)->textures[cast->texNum]->pixels[
					(cast->texY * (*map_data)->tex_width + cast->texX) * 4];
				// if (x == 0 && y == cast->drawStart)
				// {
 				// 	printf("Texture pixel values: A=%d R=%d G=%d B=%d\n", 
			   	// 	texPixel[0], texPixel[1], texPixel[2], texPixel[3]);
				// }
				  uint32_t color = (texPixel[3] << 24) | (texPixel[0] << 16) | 
							(texPixel[1] << 8) | texPixel[2];
				if (cast->side != 1)
					color = (color >> 1) & 0x7F7F7F7F;
				pixels[index] = color;
			}
			else
				pixels[index] = (*map_data)->colors->c_floor;
		}
	}
}


// ⣿⣿⣿⣿⣿⣿⠿⢋⣥⣴⣶⣶⣶⣬⣙⠻⠟⣋⣭⣭⣭⣭⡙⠻⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⡿⢋⣴⣿⣿⠿⢟⣛⣛⣛⠿⢷⡹⣿⣿⣿⣿⣿⣿⣆⠹⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⡿⢁⣾⣿⣿⣴⣿⣿⣿⣿⠿⠿⠷⠥⠱⣶⣶⣶⣶⡶⠮⠤⣌⡙⢿⣿⣿ //
// ⣿⡿⢛⡁⣾⣿⣿⣿⡿⢟⡫⢕⣪⡭⠥⢭⣭⣉⡂⣉⡒⣤⡭⡉⠩⣥⣰⠂⠹⣿ //
// ⡟⢠⣿⣱⣿⣿⣿⣏⣛⢲⣾⣿⠃⠄⠐⠈⣿⣿⣿⣿⣿⣿⠄⠁⠃⢸⣿⣿⡧⣿ //
// ⢠⣿⣿⣿⣿⣿⣿⣿⣿⣇⣊⠙⠳⠤⠤⠾⣟⠛⠍⣹⣛⣛⣢⣀⣠⣛⡯⢉⣰⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡶⠶⢒⣠⣼⣿⣿⣛⠻⠛⢛⣛⠉⣴⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡿⢛⡛⢿⣿⣿⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡈⢿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⠸⣿⡻⢷⣍⣛⠻⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⢇⡘⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣷⣝⠻⠶⣬⣍⣛⣛⠓⠶⠶⠶⠤⠬⠭⠤⠶⠶⠞⠛⣡⣿⣿ //
// ⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣬⣭⣍⣙⣛⣛⣛⠛⠛⠛⠿⠿⠿⠛⣠⣿⣿⣿ //
// ⣦⣈⠉⢛⠻⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⠛⣁⣴⣾⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣶⣮⣭⣁⣒⣒⣒⠂⠠⠬⠭⠭⠭⢀⣀⣠⣄⡘⠿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡈⢿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⠿⠿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⣉⡥⠶⢶⣿⣿⣿⣿⣷⣆⠉⠛⠿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡿⢡⡞⠁⠀⠀⠤⠈⠿⠿⠿⠿⣿⠀⢻⣦⡈⠻⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡇⠘⡁⠀⢀⣀⣀⣀⣈⣁⣐⡒⠢⢤⡈⠛⢿⡄⠻⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⡇⠀⢀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⠉⠐⠄⡈⢀⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⠇⢠⣿⣿⣿⣿⡿⢿⣿⣿⣿⠁⢈⣿⡄⠀⢀⣀⠸⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⡿⠟⣡⣶⣶⣬⣭⣥⣴⠀⣾⣿⣿⣿⣶⣾⣿⣧⠀⣼⣿⣷⣌⡻⢿⣿ //
// ⣿⣿⠟⣋⣴⣾⣿⣿⣿⣿⣿⣿⣿⡇⢿⣿⣿⣿⣿⣿⣿⡿⢸⣿⣿⣿⣿⣷⠄⢻ //
// ⡏⠰⢾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⢂⣭⣿⣿⣿⣿⣿⠇⠘⠛⠛⢉⣉⣠⣴⣾ //
// ⣿⣷⣦⣬⣍⣉⣉⣛⣛⣉⠉⣤⣶⣾⣿⣿⣿⣿⣿⣿⡿⢰⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡘⣿⣿⣿⣿⣿⣿⣿⣿⡇⣼⣿⣿⣿⣿⣿⣿⣿⣿ //
// ⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⢸⣿⣿⣿⣿⣿⣿⣿⠁⣿⣿⣿⣿⣿⣿⣿⣿⣿ //

