/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:23 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/23 14:34:40 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

static int	count_words(char *str, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			count++;
		if (str[i] != c && str[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	int		i;
	int		start;
	int		end;
	int		element;
	char	**result;

	i = 0;
	element = 0;
	if (!s)
		return (NULL);
	result = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!result)
		return (NULL);
	while (s[i] && element < count_words((char *)s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			end = ++i;
		result[element] = ft_substr(s, start, end - start);
		if (!result[element++])
			return (NULL);
	}
	return (result);
}

void	ft_err(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	gcollector(0, 0);
	exit(EXIT_FAILURE);
}
