/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:35:38 by oel-feng          #+#    #+#             */
/*   Updated: 2025/01/19 23:53:32 by oel-feng         ###   ########.fr       */
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

// static unsigned int get_rgb(int r, int g, int b)
// {
// 	return (r << 24 | g << 16 | b << 8 | 0xFF);
// }

void raycasting(t_map_data *map_data)
{
	t_cast	cast = map_data->cast;
	const int width = WIDTH;
	const int height = HEIGHT;
	uint32_t* pixels = (uint32_t*)map_data->data_mlx->image->pixels;

	for (int x = 0; x < width; x++)
	{
		cast.cameraX = 2 * x / (double)width - 1;
		cast.rayDirX = map_data->player->dirX + map_data->player->planeX * cast.cameraX;
		cast.rayDirY = map_data->player->dirY + map_data->player->planeY * cast.cameraX;
		cast.mapX = map_data->player->x_pos_map;
		cast.mapY = map_data->player->y_pos_map;
		cast.deltaDistX = (cast.rayDirX == 0) ? 1e30 : fabs(1 / cast.rayDirX);
		cast.deltaDistY = (cast.rayDirY == 0) ? 1e30 : fabs(1 / cast.rayDirY);
		if (cast.rayDirX < 0)
		{
			cast.stepX = -1;
			cast.sideDistX = (map_data->player->x_pos_map - cast.mapX) * cast.deltaDistX;
		}
		else
		{
			cast.stepX = 1;
			cast.sideDistX = (cast.mapX + 1.0 - map_data->player->x_pos_map) * cast.deltaDistX;
		}
		if (cast.rayDirY < 0)
		{
			cast.stepY = -1;
			cast.sideDistY = (map_data->player->y_pos_map - cast.mapY) * cast.deltaDistY;
		}
		else
		{
			cast.stepY = 1;
			cast.sideDistY = (cast.mapY + 1.0 - map_data->player->y_pos_map) * cast.deltaDistY;
		}
		cast.hit = 0;
		while (cast.hit == 0)
		{
			if (cast.sideDistX < cast.sideDistY)
			{
				cast.sideDistX += cast.deltaDistX;
				cast.mapX += cast.stepX;
				cast.side = 0;
			}
			else
			{
				cast.sideDistY += cast.deltaDistY;
				cast.mapY += cast.stepY;
				cast.side = 1;
			}
			if (cast.mapX < 0 || cast.mapX >= width || 
				cast.mapY < 0 || cast.mapY >= height)
				break;
			if (map_data->map[cast.mapY][cast.mapX] == '1')
				cast.hit = 1;
		}
		if (cast.side == 0)
			cast.perpWallDist = (cast.mapX - map_data->player->x_pos_map + 
							   (1 - cast.stepX) / 2) / cast.rayDirX;
		else
			cast.perpWallDist = (cast.mapY - map_data->player->y_pos_map + 
							   (1 - cast.stepY) / 2) / cast.rayDirY;
		if (cast.perpWallDist < 0.1)
			cast.perpWallDist = 0.1;
		cast.lineHeight = (int)(height / cast.perpWallDist);
		if (cast.lineHeight > height * 10)
			cast.lineHeight = height * 10;
		cast.drawStart = -cast.lineHeight / 2 + height / 2;
		cast.drawEnd = cast.lineHeight / 2 + height / 2;
		if (cast.drawStart < 0) cast.drawStart = 0;
		if (cast.drawEnd >= height) cast.drawEnd = height - 1;
		if (cast.side == 0)
			cast.wallX = map_data->player->y_pos_map + cast.perpWallDist * cast.rayDirY;
		else
			cast.wallX = map_data->player->x_pos_map + cast.perpWallDist * cast.rayDirX;
		cast.wallX -= floor(cast.wallX);
		cast.texX = (int)(cast.wallX * map_data->tex_width);
		if (cast.side == 0 && cast.rayDirX > 0)
			cast.texX = map_data->tex_width - cast.texX - 1;
		if (cast.side == 1 && cast.rayDirY < 0)
			cast.texX = map_data->tex_width - cast.texX - 1;
		cast.step = (double)map_data->tex_height / cast.lineHeight;
		cast.texPos = (cast.drawStart - height / 2 + cast.lineHeight / 2) * cast.step;

	   	for (int y = 0; y < height; y++)
		{
			int index = y * width + x;
			if (index < 0 || index >= width * height)
				continue;
			if (y < cast.drawStart)
				pixels[index] = map_data->colors->c_ceiling;
			else if (y < cast.drawEnd)
			{
				cast.texY = fmod(cast.texPos, map_data->tex_height);
				cast.texPos += cast.step;
				cast.texNum = 0;
				if (cast.side == 0)
					cast.texNum = cast.rayDirX > 0 ? 0 : 1;
				else
					cast.texNum = cast.rayDirY > 0 ? 2 : 3;	
				uint8_t *texPixel = &map_data->textures[cast.texNum]->pixels[(cast.texY * map_data->tex_width + cast.texX) * 4];
				uint32_t color = (texPixel[3] << 24) | (texPixel[2] << 16) | 
							(texPixel[1] << 8) | texPixel[0];
				// printf("texPixel[0]=%d, texPixel[1]=%d, texPixel[2]=%d, texPixel[3]=%d\n", texPixel[0], texPixel[1], texPixel[2], texPixel[3]);
				// uint32_t color = (texPixel[3] << 24) | (texPixel[0] << 16) | 
				// 			(texPixel[1] << 8) | texPixel[2];
				// printf("color=%d\n", color);
				// uint32_t color = get_rgb(texPixel[3], texPixel[0], texPixel[1]);
				pixels[index] = color;
			}
			else
				pixels[index] = map_data->colors->c_floor;
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

