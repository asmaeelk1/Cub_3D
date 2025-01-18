/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:27:44 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/18 14:02:20 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub.h"

static void	check_if_walls(char *line)
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
			&& line_map[i] != ' ')
			ft_err(INVALID_MAP);
		if(line_map[i] == 'N' || line_map[i] == 'S' || line_map[i] == 'W'
			|| line_map[i] == 'E')
			{
				player->x_pos_map = i;
				player->y_pos_map = i_map;
			}
	}
}

static void	is_zero_next_to_space(char *l_curr, char *prev, char *next,
		t_map_data **map)
{
	int	i;
	char *str;

	i = -1;
	str = ft_strtrim(l_curr, " ");
	if(str[0] != '1' || str[ft_strlen(str) - 1] != '1' )
		ft_err(INVALID_MAP);
	while (l_curr[++i])
	{
		if (l_curr[i] == '0' || l_curr[i] == 'N' || l_curr[i] == 'S'
			|| l_curr[i] == 'W' || l_curr[i] == 'E')
		{
			if ((i - 1 >= 0 && l_curr[i - 1] == ' ') || (i
					+ 1 < (*map)->height_map && l_curr[i + 1] == ' '))
				ft_err(INVALID_MAP);
			if (prev[i] == ' ' || next[i] == ' ')
				ft_err(INVALID_MAP);
			if (l_curr[i] != '0' && (*map)->player->if_player_exist == false)
			{
				(*map)->player->player = l_curr[i];
				(*map)->player->if_player_exist = true;
			}
			else if (l_curr[i] != '0' && (*map)->player->if_player_exist == true)
				ft_err(INVALID_MAP);
		}
	}
}

static void	is_map_valid(t_map_data **map_data)
{
	int	curr;
	int	next;
	int	prev;

	curr = -1;
	while ((*map_data)->map[++curr])
	{
		if (curr == 0 || curr == (*map_data)->height_map - 1)
			check_if_walls((*map_data)->map[curr]);
		else
		{
			next = curr + 1;
			prev = curr - 1;
			is_zero_next_to_space((*map_data)->map[curr],
				(*map_data)->map[prev], (*map_data)->map[next], map_data);
		}
	}
	if ((*map_data)->player->if_player_exist == false)
		ft_err(INVALID_MAP);
	(*map_data)->data_mlx->width = (*map_data)->width_map * TILE_SIZE;
	(*map_data)->data_mlx->height = (*map_data)->height_map * TILE_SIZE;
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
		len_current_line = ft_strlen((*map_data)->map[i_map]);
		while (len_current_line < max_len_line)
		{
			(*map_data)->map[i_map] = ft_strjoin((*map_data)->map[i_map], " ");
			len_current_line++;
		}
	}
	(*map_data)->height_map = i_map;
	(*map_data)->width_map = max_len_line;
	is_map_valid(map_data);
}
