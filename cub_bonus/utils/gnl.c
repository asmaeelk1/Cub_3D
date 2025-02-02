/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:25 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/02 21:23:46 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

int	save_fd(int fd, bool hold)
{
	static int	_fd = -1;

	if (hold)
		_fd = fd;
	return (_fd);
}

static char	*split_nl(char **save)
{
	char	*line;
	char	*tmp;
	int		i;

	i = 0;
	tmp = *save;
	while (tmp[i] && tmp[i] != '\n')
		i++;
	line = ft_substr(*save, 0, i + 1);
	if (tmp[i] == '\n')
		i++;
	*save = ft_strdup(tmp + i);
	return (line);
}

static char	*read_line(int fd, char *save)
{
	char	*buff;
	int		readret;

	buff = gcollector((size_t)BUFFER_SIZE + 1, 1);
	if (!buff)
		return (NULL);
	buff[0] = 0;
	readret = 1;
	while (readret && !ft_strchr(save, '\n'))
	{
		readret = read(fd, buff, BUFFER_SIZE);
		if (readret == -1)
			return (NULL);
		buff [readret] = '\0';
		save = ft_strjoin(save, buff);
		if (!*save)
			return (NULL);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_line(fd, save);
	if (!save)
		return (NULL);
	str = split_nl(&save);
	return (str);
}
