
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-08 10:52:13 by asel-kha          #+#    #+#             */
/*   Updated: 2025-01-08 10:52:13 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

void	plot_line(t_map_data **data, t_p p0, t_p p1, long color)
{
	t_plotline	vars;

	vars.dx = abs(p1.x - p0.x);
	vars.dy = abs(p1.y - p0.y);
	((p0.x < p1.x) && (vars.sx = 1)) || (vars.sx = -1);
	((p0.y < p1.y) && (vars.sy = 1)) || (vars.sy = -1);
	vars.err = vars.dx - vars.dy;
	while (1)
	{
		if (p0.x >= 0 && p0.y >= 0 && p0.x < WIDTH && p0.y < HEIGHT)
			mlx_put_pixel((*data)->data_mlx->image, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		vars.e2 = 2 * vars.err;
		if (vars.e2 > -vars.dy)
		{
			vars.err -= vars.dy;
			p0.x += vars.sx;
		}
		if (vars.e2 < vars.dx)
		{
			vars.err += vars.dx;
			p0.y += vars.sy;
		}
	}
}

void		draw_square(t_map_data **data, int x, int y, long color)
{
    int i;
    int j;
    int start_x = x;
    int start_y = y;
    
    i = 0;
    while (i < TILE_SIZE)
    {
        j = 0;
        while (j < TILE_SIZE)
        {
            if (start_x + i < (*data)->data_mlx->width && 
                start_y + j < (*data)->data_mlx->height)
                mlx_put_pixel((*data)->data_mlx->image, 
                    start_x + i, start_y + j, color);
            j++;
        }
        i++;
    }
}
