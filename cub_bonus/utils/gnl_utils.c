/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghriyba <ghriyba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:04:03 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/21 22:46:11 by ghriyba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

char	*ft_strchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	res = gcollector(len + 1, 1);
	if (!res)
		return (NULL);
	while (s[start] && i < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = gcollector(ft_strlen(s1) + 1, 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*tmp;
	size_t			i;

	i = 0;
	if ((int)size < 0 || (int)count < 0)
		return (NULL);
	tmp = gcollector(count * size, 1);
	if (!tmp)
		exit(EXIT_FAILURE);
	while (i < (count * size))
	{
		tmp[i] = 0;
		i++;
	}
	return (tmp);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*rtn;
	int		i;
	int		e;

	e = 0;
	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	rtn = gcollector(ft_strlen(s1) + ft_strlen(s2) + 1, 1);
	if (!rtn)
		return (NULL);
	while (s1[i])
		rtn[e++] = s1[i++];
	i = 0;
	while (s2[i])
		rtn[e++] = s2[i++];
	rtn[e] = '\0';
	return (rtn);
}
