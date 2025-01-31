/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghriyba <ghriyba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:24:32 by asel-kha          #+#    #+#             */
/*   Updated: 2025/01/31 02:20:01 by ghriyba          ###   ########.fr       */
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

static int	len_int(long nbr)
{
	int	count;

	count = 0;
	if (nbr < 0)
	{
		count++;
		nbr *= -1;
	}
	while (nbr > 0)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	nbr;

	if (n == 0)
		return (ft_strdup("0"));
	nbr = n;
	i = len_int(nbr);
	res = gcollector(i + 1, 1);
	if (!res)
		return (NULL);
	if (nbr < 0)
	{
		res[0] = '-';
		nbr *= -1;
	}
	res[i--] = '\0';
	while (nbr > 0)
	{
		res[i] = nbr % 10 + '0';
		nbr = nbr / 10;
		i--;
	}
	return (res);
}
