/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:35:38 by oel-feng          #+#    #+#             */
/*   Updated: 2025/01/18 14:24:27 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

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
		cast->lineHeight = (int)(height / cast->perpWallDist);
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
				if (x == 0 && y == cast->drawStart)
				{
 					printf("Texture pixel values: A=%d R=%d G=%d B=%d\n", 
			   		texPixel[0], texPixel[1], texPixel[2], texPixel[3]);
				}
				  uint32_t color = (texPixel[3] << 24) | (texPixel[0] << 16) | 
                            (texPixel[1] << 8) | texPixel[2];
				// if (cast->side == 1)
				// 	color = (color >> 1) & 0xFFFFFFFF;
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

// void	recheck_text(t_map_data **map_data)
// {
// 	int i;

// 	if ((*map_data)->arr_text)
// 	{
// 		i = -1;
// 		while (++i < 4)
// 			free((*map_data)->arr_text[i]);
// 		free((*map_data)->arr_text);
// 	}
// 	(*map_data)->arr_text = malloc((*map_data)->data_mlx->width * sizeof(int *));
// 	i = -1;
// 	while (++i < (*map_data)->data_mlx->width)
// 		(*map_data)->arr_text[i] = malloc((*map_data)->data_mlx->height * sizeof(int));
// }

// void load_textures(t_map_data *map_data)
// {
// 	map_data->textures[0] = mlx_load_png("./textures/test.png");
// 	map_data->textures[1] = mlx_load_png("./textures/test.png");
// 	map_data->textures[2] = mlx_load_png("./textures/test.png");
// 	map_data->textures[3] = mlx_load_png("./textures/test.png");
// 	if (!map_data->textures[0] || !map_data->textures[1] || !map_data->textures[2] || !map_data->textures[3])
// 		ft_err("Error: Failed to load textures");
// 	map_data->tex_width = map_data->textures[0]->width;
// 	map_data->tex_height = map_data->textures[0]->height;
// }

// void start_raycast(t_map_data **map_data)
// {
// 	if (!map_data || !*map_data || !(*map_data)->data_mlx)
// 	{
// 		printf("Invalid map_data in start_raycast\n");
// 		return;
// 	}

// 	// printf("MLX: %p\n", (*map_data)->data_mlx->mlx);
// 	// printf("Image: %p\n", (*map_data)->data_mlx->image);
	
// 	t_cast cast = (*map_data)->cast;
// 	// recheck_text(map_data);
// 	raycasting_init(&cast);
// 	load_textures(*map_data);
// 	// raycasting_init(&cast);
// 	raycasting(map_data, &cast);
// }

// void raycasting_init(t_cast *cast)
// {
// 	cast->cameraX = 0;
// 	cast->rayDirX = 0;
// 	cast->rayDirY = 0;
// 	cast->mapX = 0;
// 	cast->mapY = 0;
// 	cast->sideDistX = 0;
// 	cast->sideDistY = 0;
// 	cast->deltaDistX = 0;
// 	cast->deltaDistY = 0;
// 	cast->perpWallDist = 0;
// 	cast->posX = 0;
// 	cast->stepX = 0;
// 	cast->stepY = 0;
// 	cast->hit = 0;
// 	cast->side = 0;
// 	cast->lineHeight = 0;
// 	cast->drawStart = 0;
// 	cast->drawEnd = 0;
// }

// void raycasting(t_map_data **map_data, t_cast *cast)
// {
// 	if (!map_data || !*map_data || !(*map_data)->data_mlx || !(*map_data)->data_mlx->image)
// 	{
// 		printf("Error: Invalid pointers in raycasting\n");
// 		return;
// 	}
// 	// printf("Player position: x=%d, y=%d\n", (*map_data)player->x_pos_map, (*map_data)player->y_pos_map);
//     // printf("Player direction: dirX=%f, dirY=%f\n", (*map_data)player->dirX, (*map_data)player->dirY);
//     // printf("Camera plane: planeX=%f, planeY=%f\n", (*map_data)player->planeX, (*map_data)player->planeY);

// 	const int width = (*map_data)->data_mlx->image->width;
// 	const int height = (*map_data)->data_mlx->image->height;
// 	uint32_t* pixels = (uint32_t*)(*map_data)->data_mlx->image->pixels;


// 	////////////////////////////////////////////
// 	// Need to incorprate these values into either player struct or cast struct
// 	///////////////////////////////////////////
//     // (*map_data)->player->dirX = cos(map_data->player->rotation_angle);
//     // (*map_data)->player->dirY = sin(map_data->player->rotation_angle);
//     // (*map_data)->player->planeX = -sin(map_data->player->rotation_angle + M_PI / 2.0);
//     // (*map_data)->player->planeY = cos(map_data->player->rotation_angle + M_PI / 2.0);
//     // Initialize other variables as needed
// 	double dirX = -1;
// 	double dirY = 0;
// 	double planeX = 0;
// 	double planeY = 0.66;
// 	////////////////////////////////////////////
// 	// Need to make these more adaptable to params passed in the player struct
// 	// double rotation = (*map_data)->player->rotation_angle;
// 	// cast->dirX = cos(rotation);
// 	// cast->dirY = sin(rotation);
// 	// cast->planeX = -sin(rotation + M_PI / 2.0);
// 	// cast->planeY = cos(rotation + M_PI / 2.0);
// 	////////////////////////////////////////////
// 	printf("----------------------\n");
// 	printf("Player's X position in map: %d\n", (*map_data)->player->x_pos_map);
// 	printf("Player's Y position in map: %d\n", (*map_data)->player->y_pos_map);
// 	printf("----------------------\n");
// 	(*map_data)->player->xc = 0;
//     (*map_data)->player->yc = 0;
//     (*map_data)->player->rotate_angle = 0.0;
//     (*map_data)->player->rotation_speed = 0.1;
//     (*map_data)->player->turn_dir = 0;
// 	// printf("Player position: x=%d, y=%d\n", (*map_data)->player->x_pos_map, (*map_data)->player->y_pos_map);
// 	// printf("Player direction: xc=%d, yc=%d\n", (*map_data)->player->xc, (*map_data)->player->yc);
// 	// for (int i = 0; i < width * height; i++)
// 	// 	pixels[i] = 0xFF000000;
// 	for (int x = 0; x < width; x++)
// 	{
// 		cast->cameraX = 2 * x / (double)width - 1;
// 		cast->rayDirX = dirX + planeX * cast->cameraX;
// 		cast->rayDirY = dirY + planeY * cast->cameraX;
// 		cast->mapX = (int)(*map_data)->player->x_pos_map;
// 		cast->mapY = (int)(*map_data)->player->y_pos_map;
// 		cast->deltaDistX = (cast->rayDirX == 0) ? 1e30 : fabs(1 / cast->rayDirX);
// 		cast->deltaDistY = (cast->rayDirY == 0) ? 1e30 : fabs(1 / cast->rayDirY);
// 		if (cast->rayDirX < 0)
// 		{
// 			cast->stepX = -1;
// 			cast->sideDistX = ((*map_data)->player->x_pos_map - cast->mapX) * cast->deltaDistX;
// 		}
// 		else
// 		{
// 			cast->stepX = 1;
// 			cast->sideDistX = (cast->mapX + 1.0 - (*map_data)->player->x_pos_map) * cast->deltaDistX;
// 		}
// 		if (cast->rayDirY < 0)
// 		{
// 			cast->stepY = -1;
// 			cast->sideDistY = ((*map_data)->player->y_pos_map - cast->mapY) * cast->deltaDistY;
// 		}
// 		else
// 		{
// 			cast->stepY = 1;
// 			cast->sideDistY = (cast->mapY + 1.0 - (*map_data)->player->y_pos_map) * cast->deltaDistY;
// 		}
// 		cast->hit = 0;
// 		while (cast->hit == 0)
// 		{
// 			if (cast->sideDistX < cast->sideDistY)
// 			{
// 				cast->sideDistX += cast->deltaDistX;
// 				cast->mapX += cast->stepX;
// 				cast->side = 0;
// 			}
// 			else
// 			{
// 				cast->sideDistY += cast->deltaDistY;
// 				cast->mapY += cast->stepY;
// 				cast->side = 1;
// 			}
// 			if (cast->mapX < 0 || cast->mapX >= (*map_data)->width_map || 
// 				cast->mapY < 0 || cast->mapY >= (*map_data)->height_map)
// 				break;
			
// 			if ((*map_data)->map[cast->mapY][cast->mapX] == '1')
// 			{
// 				cast->hit = 1;
// 				// printf("Hit wall at: mapX=%d, mapY=%d\n", cast->mapX, cast->mapY);
// 			}
// 		}
// 		if (cast->side == 0)
// 			cast->perpWallDist = (cast->mapX - (*map_data)->player->x_pos_map + 
// 							   (1 - cast->stepX) / 2) / cast->rayDirX;
// 		else
// 			cast->perpWallDist = (cast->mapY - (*map_data)->player->y_pos_map + 
// 							   (1 - cast->stepY) / 2) / cast->rayDirY;
// 		cast->lineHeight = (int)(height / cast->perpWallDist);
// 		cast->drawStart = -cast->lineHeight / 2 + height / 2;
// 		cast->drawEnd = cast->lineHeight / 2 + height / 2;
// 		if (cast->drawStart < 0) cast->drawStart = 0;
// 		if (cast->drawEnd >= height) cast->drawEnd = height - 1;
// 		if (cast->side == 0)
// 			cast->wallX = (*map_data)->player->y_pos_map + cast->perpWallDist * cast->rayDirY;
// 		else
// 			cast->wallX = (*map_data)->player->x_pos_map + cast->perpWallDist * cast->rayDirX;
// 		cast->wallX -= floor(cast->wallX);
// 		cast->texX = (int)(cast->wallX * (*map_data)->tex_width);
//         if (cast->side == 0 && cast->rayDirX > 0)
//             cast->texX = (*map_data)->tex_width - cast->texX - 1;
//         if (cast->side == 1 && cast->rayDirY < 0)
//             cast->texX = (*map_data)->tex_width - cast->texX - 1;
// 		cast->step = (double)(*map_data)->tex_height / cast->lineHeight;
//         cast->texPos = (cast->drawStart - height / 2 + cast->lineHeight / 2) * cast->step;

// 	   	for (int y = 0; y < height; y++)
//         {
//             int index = y * width + x;
//             if (index < 0 || index >= width * height)
//                 continue;
//             if (y < cast->drawStart)
//                 pixels[index] = 0xFF0000FF;
//             else if (y < cast->drawEnd)
//             {
//                 cast->texY = (int)cast->texPos & ((*map_data)->tex_height - 1);
//                 cast->texPos += cast->step;
//                 cast->texNum = 0;
//                 if (cast->side == 0)
//                     cast->texNum = cast->rayDirX > 0 ? 0 : 1;
//                 else
//                     cast->texNum = cast->rayDirY > 0 ? 2 : 3;
//                 uint8_t *texPixel = &(*map_data)->textures[cast->texNum]->pixels[
//                     (cast->texY * (*map_data)->tex_width + cast->texX) * 4];
//                 // uint32_t color = (texPixel[3] << 24) | (texPixel[0] << 16) | 
//                 //                 (texPixel[1] << 8) | texPixel[2];
// 				uint32_t color = rgb_to_int(texPixel[3], texPixel[0], texPixel[1], texPixel[2]);
//                 if (cast->side == 1)
//                     color = (color >> 1) & 0x7F7F7F7F;
//                 pixels[index] = color;
//             }
//             else
//                 pixels[index] = 0xFFFF0000;
//         }
//     }
// }