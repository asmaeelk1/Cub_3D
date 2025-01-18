/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_backup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:36:11 by oel-feng          #+#    #+#             */
/*   Updated: 2025/01/18 16:52:53 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/cub.h"



// void	rendering(t_map_data **map_data)
// {
// 	t_textures_img	*text;
// 	int			x;
// 	int			y;

// 	text = gcollector(sizeof(t_textures_img), 1);
// 	text->image = NULL;
// 	text->address = NULL;
// 	text->line = 0;
// 	text->pixels = 0;
// 	text->endian = 0;
// 	text->image = mlx_new_image((*map_data)->data_mlx->mlx, (*map_data)->data_mlx->width, (*map_data)->data_mlx->height);
// 	if (!text->image)
// 		ft_err("Error: Memory allocation failed");
// 	text->address = (int *)mlx_get_data_addr(text->image, &text->pixels, &text->line, &text->endian);
// 	x = -1;
// 	while (++x < (*map_data)->data_mlx->height)
// 	{
// 		y = -1;
// 		while (++y < (*map_data)->data_mlx->width)
// 			text->address[(*map_data)->data_mlx->width * y + x] = (*map_data)->arr_text[x][y];
// 	}
// 	// mlx_image_to_window((*map_data)->data_mlx->mlx, (*map_data)->data_mlx->image, 0, 0);
// 	mlx_image_to_window((*map_data)->data_mlx->mlx, text->image, 0, 0);
// 	mlx_close_window((*map_data)->data_mlx->mlx);
// }

// void    start_raycast(t_map_data **map_data)
// {
// 	if (!map_data || !*map_data)
//     {
//         printf("Error: Invalid map_data\n");
//         return;
//     }
	
//     if (!(*map_data)->data_mlx)
//     {
//         printf("Error: data_mlx is NULL\n");
//         return;
//     }
	
//     if (!(*map_data)->data_mlx->mlx)
//     {
//         printf("Error: MLX instance is NULL\n");
//         return;
//     }
	
//     if (!(*map_data)->data_mlx->image)
//     {
//         printf("Error: MLX image is NULL\n");
//         return;
//     }
	
//     printf("Window dimensions: %d x %d\n", (*map_data)->data_mlx->width, (*map_data)->data_mlx->height);
//     printf("Map dimensions: %d x %d\n", (*map_data)->width_map, (*map_data)->height_map);
//     printf("Player position: (%d, %d)\n", (*map_data)->player->x_pos_map, (*map_data)->player->y_pos_map);
//     printf("Player direction: (%d, %d)\n", (*map_data)->player->xc, (*map_data)->player->yc);

// 	t_cast  cast;
// 	int     x;

// 	x = 0;
// 	cast = (*map_data)->cast;
// 	recheck_text(map_data);
// 	load_textures(*map_data);
// 	raycasting_init(&cast);
// 	raycasting(map_data, &cast);
// 	// rendering(map_data);
// }

// void	mlx_my_draw_line(void *mlx, int x, int y, int x1, int y1, int color)
// {
// 	t_plotline	vars;

// 	vars.dx = abs(x1 - x);
// 	vars.dy = abs(y1 - y);
// 	vars.sx = x < x1 ? 1 : -1;
// 	vars.sy = y < y1 ? 1 : -1;
// 	vars.err = (vars.dx > vars.dy ? vars.dx : -vars.dy) / 2;
// 	while (x != x1 || y != y1)
// 	{
// 		if (x >= 0 && y >= 0 && x < 800 && y < 800)
// 			mlx_put_pixel(mlx, x, y, color);
// 		vars.e2 = vars.err;
// 		if (vars.e2 > -vars.dx)
// 		{
// 			vars.err -= vars.dy;
// 			x += vars.sx;
// 		}
// 		if (vars.e2 < vars.dy)
// 		{
// 			vars.err += vars.dx;
// 			y += vars.sy;
// 		}
// 	}
// }

// void	raycasting(t_map_data **map_data, t_cast *cast)
// {
// 	int x;
// 	int	y;
// 	double planeX = 0;
//     double planeY = 0.66;
	
// 	if (!map_data || !*map_data || !(*map_data)->data_mlx || !(*map_data)->data_mlx->image)
//     {
//         ft_err("Error: Invalid MLX data");
//         return;
//     }

//     int width = (*map_data)->data_mlx->width;
//     int height = (*map_data)->data_mlx->height;
//     x = 0;
//     while (x < width)
//     {
//         cast->cameraX = 2 * x / (double)width - 1;
//         cast->rayDirX = (*map_data)->player->xc + planeX * cast->cameraX;
//         cast->rayDirY = (*map_data)->player->yc + planeY * cast->cameraX;
//         cast->mapX = (int)(*map_data)->player->x_pos_map;
//         cast->mapY = (int)(*map_data)->player->y_pos_map;
//         cast->deltaDistX = (cast->rayDirX == 0) ? 1e30 : fabs(1 / cast->rayDirX);
//         cast->deltaDistY = (cast->rayDirY == 0) ? 1e30 : fabs(1 / cast->rayDirY);
//         cast->hit = 0;
//         if (cast->rayDirX < 0)
//         {
//             cast->stepX = -1;
//             cast->sideDistX = ((*map_data)->player->x_pos_map - cast->mapX) * cast->deltaDistX;
//         }
//         else
//         {
//             cast->stepX = 1;
//             cast->sideDistX = (cast->mapX + 1.0 - (*map_data)->player->x_pos_map) * cast->deltaDistX;
//         }
//         if (cast->rayDirY < 0)
//         {
//             cast->stepY = -1;
//             cast->sideDistY = ((*map_data)->player->y_pos_map - cast->mapY) * cast->deltaDistY;
//         }
//         else
//         {
//             cast->stepY = 1;
//             cast->sideDistY = (cast->mapY + 1.0 - (*map_data)->player->y_pos_map) * cast->deltaDistY;
//         }
//         while (cast->hit == 0)
//         {
//             if (cast->sideDistX < cast->sideDistY)
//             {
//                 cast->sideDistX += cast->deltaDistX;
//                 cast->mapX += cast->stepX;
//                 cast->side = 0;
//             }
//             else
//             {
//                 cast->sideDistY += cast->deltaDistY;
//                 cast->mapY += cast->stepY;
//                 cast->side = 1;
//             }
//             if (cast->mapX < 0 || cast->mapX >= (*map_data)->width_map || 
//                 cast->mapY < 0 || cast->mapY >= (*map_data)->height_map)
//                 break;
//             if ((*map_data)->map[cast->mapY][cast->mapX] == '1')
//                 cast->hit = 1;
//         }
//         if (cast->side == 0)
//             cast->perpWallDist = (cast->mapX - (*map_data)->player->x_pos_map + (1 - cast->stepX) / 2) / cast->rayDirX;
//         else
//             cast->perpWallDist = (cast->mapY - (*map_data)->player->y_pos_map + (1 - cast->stepY) / 2) / cast->rayDirY;
//         cast->lineHeight = (int)(height / cast->perpWallDist);
//         cast->drawStart = -cast->lineHeight / 2 + height / 2;
//         if (cast->drawStart < 0)
//             cast->drawStart = 0;
//         cast->drawEnd = cast->lineHeight / 2 + height / 2;
//         if (cast->drawEnd >= height)
//             cast->drawEnd = height - 1;
//         y = 0;
//         while (y < cast->drawStart && y < height)
//         {
//             if (x >= 0 && x < width)
//                 mlx_put_pixel((*map_data)->data_mlx->image, x, y, 0x444444);
//             y++;
//         }
//         y = cast->drawStart;
//         while (y < cast->drawEnd && y < height)
//         {
//             if (x >= 0 && x < width)
//             {
//                 uint32_t color = cast->side == 0 ? 0xFF0000 : 0xCC0000;
//                 mlx_put_pixel((*map_data)->data_mlx->image, x, y, color);
//             }
//             y++;
//         }
//         y = cast->drawEnd;
//         while (y < height)
//         {
//             if (x >= 0 && x < width)
//                 mlx_put_pixel((*map_data)->data_mlx->image, x, y, 0x888888);
//             y++;
//         }
//         x++;
//     }
// }

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

// void raycasting(t_map_data **map_data, t_cast *cast)
// {
//     int x;
//     int y;
//     double planeX = 0;
//     double planeY = 0.66;

//     if (!map_data || !*map_data || !(*map_data)->data_mlx || !(*map_data)->data_mlx->image)
//     {
//         printf("Error: Invalid pointers in raycasting\n");
//         return;
//     }
//     int width = (*map_data)->data_mlx->image->width;
//     int height = (*map_data)->data_mlx->image->height;
// 	uint32_t* pixels = (uint32_t*)(*map_data)->data_mlx->image->pixels;
//     for (int i = 0; i < width * height; ++i)
//         pixels[i] = 0x000000FF;
//     (*map_data)->player->xc = -1;
//     (*map_data)->player->yc = 0;
//     for (int i = 0; i < width * height; ++i)
// 	{
//         uint32_t* pixels = (uint32_t*)(*map_data)->data_mlx->image->pixels;
//         pixels[i] = 0x000000FF;
//     }
	
//     x = 0;
//     while (x < width)
//     {
//         cast->cameraX = 2 * x / (double)width - 1;
//         cast->rayDirX = (*map_data)->player->xc + planeX * cast->cameraX;
//         cast->rayDirY = (*map_data)->player->yc + planeY * cast->cameraX;
//         cast->mapX = (int)(*map_data)->player->x_pos_map;
//         cast->mapY = (int)(*map_data)->player->y_pos_map;
//         cast->deltaDistX = (cast->rayDirX == 0) ? 1e30 : fabs(1 / cast->rayDirX);
//         cast->deltaDistY = (cast->rayDirY == 0) ? 1e30 : fabs(1 / cast->rayDirY);
//         cast->hit = 0;
//         if (cast->rayDirX < 0)
//         {
//             cast->stepX = -1;
//             cast->sideDistX = ((*map_data)->player->x_pos_map - cast->mapX) * cast->deltaDistX;
//         }
//         else
//         {
//             cast->stepX = 1;
//             cast->sideDistX = (cast->mapX + 1.0 - (*map_data)->player->x_pos_map) * cast->deltaDistX;
//         }
//         if (cast->rayDirY < 0)
//         {
//             cast->stepY = -1;
//             cast->sideDistY = ((*map_data)->player->y_pos_map - cast->mapY) * cast->deltaDistY;
//         }
//         else
//         {
//             cast->stepY = 1;
//             cast->sideDistY = (cast->mapY + 1.0 - (*map_data)->player->y_pos_map) * cast->deltaDistY;
//         }
//         while (cast->hit == 0)
//         {
//             if (cast->sideDistX < cast->sideDistY)
//             {
//                 cast->sideDistX += cast->deltaDistX;
//                 cast->mapX += cast->stepX;
//                 cast->side = 0;
//             }
//             else
//             {
//                 cast->sideDistY += cast->deltaDistY;
//                 cast->mapY += cast->stepY;
//                 cast->side = 1;
//             }
			
//             if (cast->mapX < 0 || cast->mapX >= (*map_data)->width_map || 
//                 cast->mapY < 0 || cast->mapY >= (*map_data)->height_map)
//                 break;
				
//             if ((*map_data)->map[cast->mapY][cast->mapX] == '1')
//                 cast->hit = 1;
//         }
//         if (cast->side == 0)
//             cast->perpWallDist = (cast->mapX - (*map_data)->player->x_pos_map + 
//                                 (1 - cast->stepX) / 2) / cast->rayDirX;
//         else
//             cast->perpWallDist = (cast->mapY - (*map_data)->player->y_pos_map + 
//                                 (1 - cast->stepY) / 2) / cast->rayDirY;
//         cast->lineHeight = (int)(height / cast->perpWallDist);
//         cast->drawStart = -cast->lineHeight / 2 + height / 2;
//         if (cast->drawStart < 0)
//             cast->drawStart = 0;
//         cast->drawEnd = cast->lineHeight / 2 + height / 2;
//         if (cast->drawEnd >= height)
//             cast->drawEnd = height - 1;
//         uint32_t* pixels = (uint32_t*)(*map_data)->data_mlx->image->pixels;
//         for (y = 0; y < cast->drawStart && y < height; y++)
//         {
//             int index = y * width + x;
//             if (index >= 0 && index < (width * height))
//                 pixels[index] = 0x444444FF;
//         }
//         for (y = cast->drawStart; y < cast->drawEnd && y < height; y++)
//         {
//             int index = y * width + x;
//             if (index >= 0 && index < (width * height))
//             {
//                 uint32_t color = cast->side == 0 ? 0xFF0000FF : 0xCC0000FF;
//                 pixels[index] = color;
//             }
//         }
//         for (y = cast->drawEnd; y < height; y++)
//         {
//             int index = y * width + x;
//             if (index >= 0 && index < (width * height))
//                 pixels[index] = 0x888888FF;
//         }
//         x++;
//     }
// }

// void raycasting(t_map_data **map_data, t_cast *cast)
// {
// 	(void)cast;
//     if (!map_data || !*map_data || !(*map_data)->data_mlx)
//     {
//         printf("Invalid map_data or data_mlx\n");
//         return;
//     }
//     if (!(*map_data)->data_mlx->image)
//     {
//         printf("MLX image is NULL\n");
//         return;
//     }

//     printf("Starting basic rendering test...\n");

//     (*map_data)->player->xc = -1;
//     (*map_data)->player->yc = 0;

//     for (int y = 0; y < 100 && y < (*map_data)->data_mlx->height; y++)
//     {
//         for (int x = 0; x < 100 && x < (*map_data)->data_mlx->width; x++)
//         {
//             if (x % 2 == 0 && y % 2 == 0)
//             {
//                 printf("Drawing pixel at %d,%d\n", x, y);
//                 mlx_put_pixel((*map_data)->data_mlx->image, x, y, 0xFF0000);
//             }
//         }
//     }
	
//     printf("Basic rendering test complete\n");
// }

// void start_raycast(t_map_data **map_data)
// {
//     if (!map_data || !*map_data || !(*map_data)->data_mlx)
//     {
//         printf("Invalid map_data in start_raycast\n");
//         return;
//     }

//     printf("MLX: %p\n", (*map_data)->data_mlx->mlx);
//     // printf("Window: %p\n", (*map_data)->data_mlx->window);
//     printf("Image: %p\n", (*map_data)->data_mlx->image);
	
//     t_cast cast = (*map_data)->cast;
//     raycasting(map_data, &cast);
// }

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