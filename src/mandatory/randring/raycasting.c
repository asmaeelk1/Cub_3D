/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 05:35:38 by oel-feng          #+#    #+#             */
/*   Updated: 2025/01/17 16:14:48 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	recheck_text(t_map_data **map_data)
{
	int i;

	if ((*map_data)->arr_text)
	{
		i = -1;
		while (++i < 4)
			free((*map_data)->arr_text[i]);
		free((*map_data)->arr_text);
	}
	(*map_data)->arr_text = gcollector(((*map_data)->data_mlx->width + 1) * sizeof(int *), 1);
	i = -1;
	while (++i < (*map_data)->data_mlx->width)
		(*map_data)->arr_text[i] = gcollector((*map_data)->data_mlx->height * sizeof(int), 1);
}

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

void    start_raycast(t_map_data **map_data)
{
	t_cast  cast;
	int     x;

	x = 0;
	cast = (*map_data)->cast;
	recheck_text(map_data);
	raycasting_init(&cast);
	raycasting(map_data, &cast);
	// rendering(map_data);
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

void	raycasting(t_map_data **map_data, t_cast *cast)
{
	int x;
	int	j;

	x = 0;
	while (x < (*map_data)->width_map)
	{
		raycasting_init(cast);
		cast->cameraX = 2 * x / (double)(*map_data)->width_map - 1;
		cast->rayDirX = (*map_data)->player->xc + (*map_data)->player->xc * cast->cameraX;
		cast->rayDirY = (*map_data)->player->yc + (*map_data)->player->yc * cast->cameraX;
		cast->mapX = (int)(*map_data)->player->x_pos_map;
		cast->mapY = (int)(*map_data)->player->y_pos_map;
		cast->deltaDistX = fabs(1 / cast->rayDirX);
		cast->deltaDistY = fabs(1 / cast->rayDirY);
		cast->hit = 0;
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
			if (cast->mapY < 0.25 || cast->mapX < 0.25 || cast->mapY > (*map_data)->height_map - 0.25 || cast->mapX > (*map_data)->width_map - 1.25)
				break;
			else if ((*map_data)->map[cast->mapY][cast->mapX] == '1')
				cast->hit = 1;
		}
		if (cast->side == 0)
			cast->perpWallDist = cast->sideDistX - cast->deltaDistX;
		else
			cast->perpWallDist = cast->sideDistY - cast->deltaDistY;
		cast->lineHeight = (int)((*map_data)->height_map / cast->perpWallDist);
		cast->drawStart = -cast->lineHeight / 2 + (*map_data)->height_map / 2;
		if (cast->drawStart < 0)
			cast->drawStart = 0;
		cast->drawEnd = cast->lineHeight / 2 + (*map_data)->height_map / 2;
		if (cast->drawEnd >= (*map_data)->height_map)
			cast->drawEnd = (*map_data)->height_map - 1;
		j = cast->drawStart;
		while (j < cast->drawEnd)
		{
			mlx_put_pixel((*map_data)->data_mlx->image, j, x, 0x00FF00);
			j++;
		}
		// if (cast->side == 0)
		// 	cast->posX = (*map_data)->player->y_pos_map + cast->perpWallDist * cast->rayDirY;
		// else
		// 	cast->posX = (*map_data)->player->x_pos_map + cast->perpWallDist * cast->rayDirX;
		// cast->posX -= floor(cast->posX);
		x++;
	}
}
