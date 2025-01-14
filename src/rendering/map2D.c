/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:26:38 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/14 23:01:37 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

bool is_wall(t_map_data **map_data, int x, int y)
{
	if ((*map_data)->map[(int)floor((y - 5)/ 20)][(int)floor((x - 5) /20)] == '1')
		return(true);
	else if ((*map_data)->map[(int)floor(y / 20)][(int)floor(x / 20)] == '1')
		return(true);
	else if ((*map_data)->map[(int)floor((y - 5) / 20)][(int)floor(x / 20)] == '1')
		return(true);
	else if ((*map_data)->map[(int)floor(y /20)][(int)floor((x - 5) / 20)] == '1')
		return(true);
	return(false);
}
void	draw_vector(t_map_data **map_data)
{
	t_p p1;
	t_p p2;
	p1.x = (*map_data)->player->xc;
	p1.y = (*map_data)->player->yc;
	p2.x = (*map_data)->player->xc + cos((*map_data)->player->rotate_angle) * 20;
	p2.y = (*map_data)->player->yc + sin((*map_data)->player->rotate_angle) * 20;
	plot_line(map_data, p1, p2, 16777215);
}

void draw_player(t_map_data **map_data, t_player *player, int color)
{
	player->xc = player->x_pos + 10 + (*map_data)->p_x_pos ;
	player->yc = player->y_pos + 10 + (*map_data)->p_y_pos;
	int r = 6;
    circleBres(*map_data, player, r, color);
	raycasting(map_data);
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
	draw_player(map_data, (*map_data)->player, 16777215);
}
