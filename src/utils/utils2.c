/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wabolles <wabolles@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 02:34:10 by asel-kha          #+#    #+#             */
/*   Updated: 2024/12/31 03:27:37 by wabolles         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

char	*ft_strtrim(char *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	if (!s1 || !set)
		return (NULL);
	j = ft_strlen(s1) - 1;
	if (ft_strlen (s1) == 0)
		return (ft_strdup(""));
	while (s1[i] && ft_strchr((char *)set, s1[i]))
		i++;
	while (s1[j] && ft_strchr((char *)set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - (i - 1)));
}

static bool	find_c(const char *sep, char c)
{
	while (*sep)
		if (*sep++ == c)
			return (true);
	return (false);
}

char	*ft_strtok(char *str, char *sep)
{
	static char	*hold;
	char		*token;

	if (str)
		hold = str;
	if (!hold || !*hold)
		return (NULL);
	while (*hold && find_c(sep, *hold))
		hold++;
	if (!*hold)
		return (NULL);
	token = hold;
	while (*hold && !find_c(sep, *hold))
		hold++;
	if (*hold)
		*hold++ = 0;
	return (token);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	res;
	int			sign;

	(1) && (i = -1, res = 0, sign = 1);
	if (str[0] == '-' || str[0] == '+')
	{
		(str[0] == '-') && (sign = -1);
		i++;
	}
	if (!str[0])
		ft_err(INVALID_COLOR);
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (res < 0 || res == INT32_MAX || - res == INT32_MAX)
				ft_err(INVALID_COLOR);
			res = res * 10;
			res += str[i] - 48;
		}
		else
			ft_err(INVALID_COLOR);
	}
	return (res * sign);
}
