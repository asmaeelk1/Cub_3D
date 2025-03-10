/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:27:44 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/02 21:53:24 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

void	check_if_walls(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != ' ')
			ft_err(INVALID_MAP);
	}
}

static void	check_char(char *line_map, int i_map, t_player *player)
{
	int	i;

	i = -1;
	while (line_map[++i])
	{
		if (line_map[i] != '1' && line_map[i] != '0' && line_map[i] != 'N'
			&& line_map[i] != 'S' && line_map[i] != 'W' && line_map[i] != 'E'
			&& line_map[i] != ' ' && line_map[i] != 'D')
			ft_err(INVALID_MAP);
		if (line_map[i] == 'N' || line_map[i] == 'S' || line_map[i] == 'W'
			|| line_map[i] == 'E')
		{
			player->x_pos_map = (double)i + 0.5;
			player->y_pos_map = (double)i_map + 0.5;
		}
	}
}

void	check_doors(char *l_curr, char *prev, char *next, int pos_door)
{
	if (pos_door == 0)
		ft_err(INVALID_MAP);
	if ((l_curr[pos_door - 1] != '1' || l_curr[pos_door + 1] != '1')
		&& (prev[pos_door] != '1' || next[pos_door] != '1'))
		ft_err(INVALID_MAP);
}

void	is_zero_next_to_space(char *l_curr, char *prev, char *next,
		t_map_data **map)
{
	int		i;
	char	*str;

	(1) && (i = -1, str = ft_strtrim(l_curr, " "), 0);
	if (str[0] != '1' || str[ft_strlen(str) - 1] != '1')
		ft_err(INVALID_MAP);
	while (l_curr[++i])
	{
		if (l_curr[i] == '0' || l_curr[i] == 'N' || l_curr[i] == 'S'
			|| l_curr[i] == 'W' || l_curr[i] == 'E' || l_curr[i] == 'D')
		{
			if ((i - 1 >= 0 && l_curr[i - 1] == ' ') || (i
					+ 1 < (*map)->height_map && l_curr[i + 1] == ' ')
				|| prev[i] == ' ' || next[i] == ' ')
				ft_err(INVALID_MAP);
			(l_curr[i] == 'D') && (check_doors(l_curr, prev, next, i), 0);
			if (l_curr[i] != '0' && l_curr[i] != 'D'
				&& (*map)->player->if_player_exist == false)
				(1) && ((*map)->player->player = l_curr[i],
					(*map)->player->if_player_exist = true);
			else if (l_curr[i] != '0' && l_curr[i] != 'D'
				&& (*map)->player->if_player_exist == true)
				ft_err(INVALID_MAP);
		}
	}
}

void	pars_map(t_map_data **map_data)
{
	int	i_map;
	int	max_len_line;
	int	len_current_line;

	i_map = -1;
	max_len_line = 0;
	while ((*map_data)->map[++i_map])
	{
		len_current_line = ft_strlen((*map_data)->map[i_map]);
		check_char((*map_data)->map[i_map], i_map, (*map_data)->player);
		if (max_len_line < len_current_line)
			max_len_line = len_current_line;
	}
	i_map = -1;
	while ((*map_data)->map[++i_map])
	{
		len_current_line = ft_strlen((*map_data)->map[i_map]) - 1;
		while (++len_current_line < max_len_line)
			(*map_data)->map[i_map] = ft_strjoin((*map_data)->map[i_map], " ");
	}
	(*map_data)->height_map = i_map;
	(*map_data)->width_map = max_len_line;
}
