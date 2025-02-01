/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:36:29 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/01 16:48:14 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub_bonus.h"

static int	check_file(char *file)
{
	int	i;
	int	fd;

	i = 0;
	fd = -1;
	while (file[i])
		i++;
	i--;
	while (file[i] != '.')
		i--;
	if (!ft_strcmp(file + i, ".cub"))
		fd = open(file, O_RDONLY, 0644);
	if (fd < 0)
		ft_err(FILE_NOT_FOUND);
	return (fd);
}

static void	read_map(int file_name, t_map_data **map_data)
{
	char	*line;
	char	*map_lines;

	line = get_next_line(file_name);
	map_lines = NULL;
	while (line && !ft_strncmp(ft_strtrim(line, " "), "\n", ft_strlen(line)))
		line = get_next_line(file_name);
	if (!line)
		ft_err("Empty_file");
	line = ft_strjoin(line, "\n");
	while (line)
	{
		if (line && !ft_strncmp(line, "\n", ft_strlen(line)))
			break ;
		map_lines = ft_strjoin(map_lines, line);
		line = get_next_line(file_name);
	}
	while (line && !ft_strncmp(line, "\n", ft_strlen(line)))
		line = get_next_line(file_name);
	if (line && ft_strncmp(line, "\n", ft_strlen(line)))
		ft_err(INVALID_MAP);
	(*map_data)->map = ft_split(map_lines, '\n');
	close(file_name);
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
}

void	parsing(char *file_name, t_map_data *map_data)
{
	int	fd;

	fd = check_file(file_name);
	read_elements(fd, &map_data);
	read_map(fd, &map_data);
	pars_map(&map_data);
	is_map_valid(&map_data);
}
