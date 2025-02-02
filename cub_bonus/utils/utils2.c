/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:32 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/01 16:59:46 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub_bonus.h"

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

static void	check_sign(char c)
{
	if (c == '-' || c == '+')
		ft_err(INVALID_COLOR);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;
	long long	tmp;

	(1) && (i = -1, res = 0, sign = 1);
	if (!str[0])
		ft_err(INVALID_COLOR);
	check_sign(str[0]);
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			tmp = res * 10 + (str[i] - 48);
			if (tmp < res || tmp > INT32_MAX)
				ft_err(INVALID_COLOR);
			res = tmp;
		}
		else
			ft_err(INVALID_COLOR);
	}
	return (res * sign);
}
