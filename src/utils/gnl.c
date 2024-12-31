/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:58:28 by asel-kha          #+#    #+#             */
/*   Updated: 2024/12/31 03:26:55 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*split_nl(char **save)
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

char	*read_line(int fd, char *save)
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
