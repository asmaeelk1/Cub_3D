/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghriyba <ghriyba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:23:53 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/11 20:41:38 by ghriyba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void	draw_vector(t_map_data **map_data)
{
	t_p p1;
	t_p p2;
	p1.x = (*map_data)->player->xc;
	p1.y = (*map_data)->player->yc;
	p2.x = (*map_data)->player->xc + cos((*map_data)->player->rotate_angle) * TILE_SIZE;
	p2.y = (*map_data)->player->yc + sin((*map_data)->player->rotate_angle) * TILE_SIZE;
	plot_line(map_data, p1, p2, 77657578);
}

void draw_player(t_map_data **map_data, int color)
{
	int i;
    int j;
    int start_x = (*map_data)->player->x_pos - 4;
    int start_y = (*map_data)->player->y_pos - 4;
    i = 0;
    while (i < 8)
    {
        j = 0;
        while (j < 8)
        {
            if (start_x + i < (*map_data)->data_mlx->width && 
                start_y + j < (*map_data)->data_mlx->height)
                mlx_put_pixel((*map_data)->data_mlx->image, 
                    start_x + i, start_y + j, color);
            j++;
        }
        i++;
    }
	(*map_data)->player->xc = (*map_data)->player->x_pos  + (*map_data)->p_x_pos ;
	(*map_data)->player->yc = (*map_data)->player->y_pos + (*map_data)->p_y_pos;
	draw_vector(map_data);
}

void map_2d(t_map_data **map_data)
{
    int y = 0;
	int i = -1;

    while ((*map_data)->map[++i])
    {
		int x = 0;
		int j = -1;
        while ((*map_data) && (*map_data)->map[i][++j])
        {
			if((*map_data)->map[i][j] == '1')
				draw_square(map_data, x, y, 255);
			else if((*map_data)->map[i][j] == '0')
            	draw_square(map_data, x, y, (*map_data)->colors->c_floor);
			else if((*map_data)->map[i][j] != ' ')
			{
				(*map_data)->player->x_pos = x;
				(*map_data)->player->y_pos = y;
				draw_square(map_data, x, y, (*map_data)->colors->c_floor);
			}
			x+=20;
        }
		y+=20;
    }
	draw_player(map_data, 77657578);
}
