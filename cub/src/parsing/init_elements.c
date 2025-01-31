/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:01:25 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/31 19:41:14 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

static unsigned int	rgb_to_int(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	pars_colors(char *color)
{
	int		i_rgb;
	char	*color_token;
	int		i;

	i = -1;
	i_rgb = 0;
	if (!ft_strtrim(color, " "))
		ft_err("Empty file");
	if ((ft_strlen(color) > 1 && color[ft_strlen(color) - 1] == ',') || color[0] == ',')
		ft_err(INVALID_COLOR_FORMAT);
	while (color[++i])
		if (color[i] == ',' && color[i + 1] == ',')
			ft_err(INVALID_COLOR_FORMAT);
	color_token = ft_strtok(color, ",");
	while (color_token)
	{
		if (i_rgb >= 3)
			ft_err(INVALID_COLOR_FORMAT);
		if (ft_atoi(ft_strtrim(color_token, " ")) < 0
			|| ft_atoi(ft_strtrim(color_token, " ")) > 255)
			ft_err(INVALID_COLOR);
		color_token = ft_strtok(NULL, ",");
		i_rgb++;
	}
	(i_rgb != 3) && (ft_err(INVALID_COLOR_FORMAT), 0);
}

static void	init_colors(t_colors **colors, char *line)
{
	char			**rgb;
	char			*save_line;
	unsigned int	color;

	if (!ft_strncmp(line, "\n", ft_strlen(line)))
		ft_err("invalid file");
	save_line = line;
	line[ft_strlen(line) - 1] = 0;
	line = ft_strtrim(line + 2, " ");
	pars_colors(ft_strtrim(save_line + 2, " "));
	rgb = ft_split(line, ',');
	color = rgb_to_int(255, ft_atoi(rgb[2]), ft_atoi(rgb[1]), ft_atoi(rgb[0]));
	if (!ft_strncmp(save_line, "F ", 2) && (*colors)->c_floor == -1)
		(*colors)->c_floor = color;
	else if (!ft_strncmp(save_line, "C ", 2) && (*colors)->c_ceiling == -1)
		(*colors)->c_ceiling = color;
	else
		ft_err(INVALID_MAP);
}

static void	init_textures(t_textures **textures, t_colors **colors, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && !(*textures)->north)
	{
		line[ft_strlen(line) - 1] = 0;
		(*textures)->north = ft_strtrim(line + 3, " \t");
	}
	else if (!ft_strncmp(line, "SO ", 3) && !(*textures)->south)
	{
		line[ft_strlen(line) - 1] = 0;
		(*textures)->south = ft_strtrim(line + 3, " \t");
	}
	else if (!ft_strncmp(line, "WE ", 3) && !(*textures)->west)
	{
		line[ft_strlen(line) - 1] = 0;
		(*textures)->west = ft_strtrim(line + 3, " \t");
	}
	else if (!ft_strncmp(line, "EA ", 3) && !(*textures)->east)
	{
		line[ft_strlen(line) - 1] = 0;
		(*textures)->east = ft_strtrim(line + 3, " \t");
	}
	else if(ft_strncmp(line, "C ", 2) && ft_strncmp(line, "F ", 2) )
		ft_err(INVALID_MAP);
	else
		init_colors(colors, line);
}

void	read_elements(int file_name, t_map_data **map_data)
{
	int		i_elements;
	char	*line;

	i_elements = 6;
	line = get_next_line(file_name);
	if (!line)
		ft_err("Empty file ");
	while (line && i_elements > 0)
	{
		if (!ft_strncmp(line, "\n", ft_strlen(line)))
		{
			line = get_next_line(file_name);
			continue ;
		}
		while (*line == ' ' )
			line++;
		init_textures(&(*map_data)->texts, &(*map_data)->colors, line);
		if (i_elements > 1)
			line = get_next_line(file_name);
		i_elements--;
	}
}
