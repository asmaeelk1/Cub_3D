/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 01:34:38 by oel-feng          #+#    #+#             */
/*   Updated: 2025/02/05 03:15:26 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static void	my_draw_function(t_cast *cast, t_map_data *map_data,
	uint32_t *pixels, int index)
{
	uint8_t		*texpixel;
	uint32_t	color;

	cast->tex_y = fmod(cast->tex_pos, map_data->tex_height);
	cast->tex_pos += cast->step;
	cast->tex_num = 0;
	if (cast->side == 0)
	{
		if (cast->raydir_x > 0)
			cast->tex_num = EAST;
		else
			cast->tex_num = WEST;
	}
	else
	{
		if (cast->raydir_y > 0)
			cast->tex_num = SOUTH;
		else
			cast->tex_num = NORTH;
	}
	texpixel = &map_data->textures[cast->tex_num]->pixels[(cast->tex_y
			* map_data->tex_width + cast->tex_x) * 4];
	color = (texpixel[3] << 24) | (texpixel[2] << 16)
		| (texpixel[1] << 8) | texpixel[0];
	pixels[index] = color;
}

void	set_textures_data(t_cast *cast, t_map_data *map_data, int x, int y)
{
	uint32_t	*pixels;
	int			index;

	pixels = (uint32_t *)map_data->image->pixels;
	cast->wall_x -= floor(cast->wall_x);
	cast->tex_x = (int)(cast->wall_x * map_data->tex_width);
	if (cast->side == 0 && cast->raydir_x > 0)
		cast->tex_x = map_data->tex_width - cast->tex_x - 1;
	if (cast->side == 1 && cast->raydir_y < 0)
		cast->tex_x = map_data->tex_width - cast->tex_x - 1;
	cast->step = (double)map_data->tex_height / cast->lineheight;
	cast->tex_pos = (cast->drawstart - HEIGHT
			/ 2 + cast->lineheight / 2) * cast->step;
	while (++y < HEIGHT)
	{
		index = y * WIDTH + x;
		if (index < 0 || index >= WIDTH * HEIGHT)
			continue ;
		if (y < cast->drawstart)
			pixels[index] = map_data->colors->c_ceiling;
		else if (y <= cast->drawend)
			my_draw_function(cast, map_data, pixels, index);
		else
			pixels[index] = map_data->colors->c_floor;
	}
}

void	start_textures(t_map_data *map_data)
{
	int	i;

	map_data->textures[NORTH] = mlx_load_png(map_data->texts->north);
	map_data->textures[SOUTH] = mlx_load_png(map_data->texts->south);
	map_data->textures[WEST] = mlx_load_png(map_data->texts->west);
	map_data->textures[EAST] = mlx_load_png(map_data->texts->east);
	if (!map_data->textures[NORTH] || !map_data->textures[SOUTH]
		|| !map_data->textures[WEST] || !map_data->textures[EAST])
		ft_err("Error: Failed to load textures");
	i = -1;
	while (++i < 4)
	{
		if ((int)map_data->textures[i]->height != 64
			&& (int)map_data->textures[i]->width != 64)
			ft_err("Error: Invalid texture size.");
	}
	map_data->tex_width = map_data->textures[NORTH]->width;
	map_data->tex_height = map_data->textures[NORTH]->height;
}
