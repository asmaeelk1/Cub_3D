/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:29:40 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/10 02:30:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	init_mlx_data(t_map_data **data)
{
	(*data)->data_mlx->mlx = mlx_init((*data)->width_map * TILE_SIZE, (*data)->height_map * TILE_SIZE, "Cub_3D", true);
	if (!((*data)->data_mlx->mlx))
	{
		ft_putstr_fd(mlx_strerror(mlx_errno), 2);
		return (1);
	}
	(*data)->data_mlx->image = mlx_new_image((*data)->data_mlx->mlx, (*data)->width_map * TILE_SIZE,
			(*data)->height_map * TILE_SIZE);
	if (!((*data)->data_mlx->image))
	{
		mlx_close_window((*data)->data_mlx->mlx);
		return (1);
	}
	if (mlx_image_to_window((*data)->data_mlx->mlx, (*data)->data_mlx->image, 0,
			0) == -1)
	{
		mlx_close_window((*data)->data_mlx->mlx);
		return (1);
	}
	return (0);
}

void	cleanup_and_exit(t_map_data **data)
{
	mlx_terminate((*data)->data_mlx->mlx);
	gcollector(0, 0);
	exit(EXIT_SUCCESS);
}

// void	__attribute__ ((destructor)) _leaks(void)
// {
// 	system("leaks cub3D");
// }

static void	set_data(t_map_data *map_data)
{
	map_data->colors = gcollector(sizeof(t_colors), 1);
	map_data->data_mlx = gcollector(sizeof(t_mlx_data), 1);
	map_data->textures = gcollector(sizeof(t_textures), 1);
	map_data->map = NULL;
	map_data->player = gcollector(sizeof(t_player), 1);
	map_data->player->player = '\0';
	map_data->player->if_player_exist = false;
	map_data->p_x_pos = 0;
	map_data->p_y_pos = 0;
	map_data->wall = false;
	map_data->player->rotate_angle = M_PI / 2;
	map_data->player->rotation_speed = 2 * ( M_PI / 180);
}

void	texture(t_map_data **map_data)
{
	(*map_data)->textures->north = mlx_xpm_file_to_image((*map_data)->data_mlx->mlx, (*map_data)->textures->north_path, &(*map_data)->textures->north_width, &(*map_data)->textures->north_height);
	(*map_data)->textures->south = mlx_xpm_file_to_image((*map_data)->data_mlx->mlx, (*map_data)->textures->south_path, &(*map_data)->textures->south_width, &(*map_data)->textures->south_height);
	(*map_data)->textures->west = mlx_xpm_file_to_image((*map_data)->data_mlx->mlx, (*map_data)->textures->west_path, &(*map_data)->textures->west_width, &(*map_data)->textures->west_height);
	(*map_data)->textures->east = mlx_xpm_file_to_image((*map_data)->data_mlx->mlx, (*map_data)->textures->east_path, &(*map_data)->textures->east_width, &(*map_data)->textures->east_height);
	// sprites textures hna I guess wlkn nhandliw mandatory first bla erros

}

void raycasting_init(t_cast **cast)
{
	t_cast	*tmp;

	tmp = *cast;
	tmp->cameraX = 0;
	tmp->rayDirX = 0;
	tmp->rayDirY = 0;
	tmp->mapX = 0;
	tmp->mapY = 0;
	tmp->sideDistX = 0;
	tmp->sideDistY = 0;
	tmp->deltaDistX = 0;
	tmp->deltaDistY = 0;
	tmp->perpWallDist = 0;
	tmp->posX = 0;
	tmp->stepX = 0;
	tmp->stepY = 0;
	tmp->hit = 0;
	tmp->side = 0;
	tmp->lineHeight = 0;
	tmp->drawStart = 0;
	tmp->drawEnd = 0;
}
void	raycasting(t_map_data **map_data)
{
	int		x;
	int		y;
	t_cast	*cast;

	y = 0;
	cast = gcollector(sizeof(t_cast), 1);
	raycasting_init(&cast);
	while (y < (*map_data)->height_map)
	{
		x = 0;
		while (x < (*map_data)->width_map)
		{
			// Calcul dyal pos d camera
			cast->cameraX = 2 * x / (float)(*map_data)->width_map - 1;
			cast->rayDirX = (*map_data)->player->xc + (*map_data)->player->xc * cast->cameraX;
			cast->rayDirY = (*map_data)->player->yc + (*map_data)->player->yc * cast->cameraX;
			cast->mapX = (int)(*map_data)->player->x_pos;
			cast->mapY = (int)(*map_data)->player->y_pos;
			cast->deltaDistX = fabs(1 / cast->rayDirX);
			cast->deltaDistY = fabs(1 / cast->rayDirY);
			cast->hit = 0;

			// Calcule step ou sideDist
			if (cast->rayDirX < 0)
			{
				cast->stepX = -1;
				cast->sideDistX = ((*map_data)->player->x_pos - cast->mapX) * cast->deltaDistX;
			}
			else
			{
				cast->stepX = 1;
				cast->sideDistX = (cast->mapX + 1.0 - (*map_data)->player->x_pos) * cast->deltaDistX;
			}
			if (cast->rayDirY < 0)
			{
				cast->stepY = -1;
				cast->sideDistY = ((*map_data)->player->y_pos - cast->mapY) * cast->deltaDistY;
			}
			else
			{
				cast->stepY = 1;
				cast->sideDistY = (cast->mapY + 1.0 - (*map_data)->player->y_pos) * cast->deltaDistY;
			}

			// Hna reje3t DDA
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
				if ((*map_data)->map[cast->mapY][cast->mapX] == '1')
					cast->hit = 1;
			}

			// Calcule dyal distance 3la l wall
			if (cast->side == 0)
				cast->perpWallDist = (cast->mapX - (*map_data)->player->x_pos + (1 - cast->stepX) / 2) / cast->rayDirX;
			else
				cast->perpWallDist = (cast->mapY - (*map_data)->player->y_pos + (1 - cast->stepY) / 2) / cast->rayDirY;

			// Calcule height dyal line
			cast->lineHeight = (int)((*map_data)->height_map / cast->perpWallDist);

			// Calcule start ou end dyal line
			cast->drawStart = -cast->lineHeight / 2 + (*map_data)->height_map / 2;
			if (cast->drawStart < 0)
				cast->drawStart = 0;
			cast->drawEnd = cast->lineHeight / 2 + (*map_data)->height_map / 2;
			if (cast->drawEnd >= (*map_data)->height_map)
				cast->drawEnd = (*map_data)->height_map - 1;

			// Draw line
			if (cast->side == 1)
				mlx_draw_line((*map_data)->data_mlx->mlx, x, cast->drawStart, x, cast->drawEnd, 0x00FF00); // Green for Y-side
			else
				mlx_draw_line((*map_data)->data_mlx->mlx, x, cast->drawStart, x, cast->drawEnd, 0x0000FF); // Blue for X-side
			x++;
		}
		y++;
	}
	map_data->cast = cast;
}

int	main(int ac, char **av)
{
	int			init_mlx;
	t_map_data	*map_data;

	if (ac < 2)
		return (EXIT_FAILURE);
	map_data = gcollector(sizeof(t_map_data), 1);
	set_data(map_data);
	parsing(av[1], &map_data);
	init_mlx = init_mlx_data(&map_data);
	if (init_mlx)
	{
		gcollector(0, 0);
		exit(EXIT_FAILURE);
	}
	// draw 2d_map
	// draw_square(map_data);
	map_2d(&map_data);
	textures(&map_data);
	raycasting(&map_data);
	mlx_loop_hook(map_data->data_mlx->mlx, (void *)my_keyhook, &map_data);
	mlx_loop(map_data->data_mlx->mlx);
	cleanup_and_exit(&map_data);
}
