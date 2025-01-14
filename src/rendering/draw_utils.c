
#include "../../includes/cub.h"

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

void draw_square(t_map_data **map_data, int x, int y, long color)
{
    t_p p1;
    t_p p2;

    p1.x = x;
    p1.y = y;
    p2.y = y;
    p2.x = x + 20;
    while (p1.y < (y+20))
    {
        plot_line(map_data, p1, p2, color);
        p1.y++;
        p2.y++;
    }
}

void drawCircle(t_map_data *map_data, t_player *player, int x, int y, long color)
{
    t_p p1;
	t_p p2;

    p1.x = player->xc + x;
    p1.y = player->yc  + y;
    p2.x = player->xc  - x;
    p2.y = player->yc - y;
    plot_line(&map_data, p1, p2, color);
    p1.x = player->xc  + x;
    p1.y = player->yc - y;
    p2.x = player->xc  - x;
    p2.y = player->yc + y;
    plot_line(&map_data, p1, p2, color);
    p1.x = player->xc  + y;
    p1.y = player->yc + x;
    p2.x = player->xc  - y;
    p2.y = player->yc - x;
    plot_line(&map_data, p1, p2, color);
    p1.x = player->xc  + y;
    p1.y = player->yc - x;
    p2.x = player->xc  - y;
    p2.y = player->yc + x;
    plot_line(&map_data, p1, p2, color);
}

void circleBres(t_map_data *map_data, t_player *player, int r, long color)
{
    int x;
	int	y;
    int d ;

	(1) && (x = 0, y = r, d = 3 - 2 * r, 0);
    drawCircle(map_data, player, x, y, color);
    while (y >= x)
	{
        if (d > 0)
		{
            y--; 
            d = d + 4 * (x - y) + 10;
    	}
   		else
        	d = d + 4 * x + 6;
    	x++;
        drawCircle(map_data , player, x, y, color);
    }
}
