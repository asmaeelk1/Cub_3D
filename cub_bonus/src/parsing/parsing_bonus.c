/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 06:36:29 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/02 21:23:38 by oel-feng         ###   ########.fr       */
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
	save_fd(fd, true);
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

void	parsing(char *file_name, t_map_data *map_data)
{
	int	fd;

	fd = check_file(file_name);
	read_elements(fd, &map_data);
	read_map(fd, &map_data);
	pars_map(&map_data);
}
