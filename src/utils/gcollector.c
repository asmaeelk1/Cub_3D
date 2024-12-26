/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asel-kha <asel-kha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:41:53 by hzahri            #+#    #+#             */
/*   Updated: 2024/12/01 23:35:47 by asel-kha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	clear_gc(t_gc **gc)
{
	t_gc	*tmp;
	t_gc	*node;

	tmp = *gc;
	while (tmp)
	{
		node = tmp;
		tmp = tmp->next;
		free(node->content);
		free(node);
	}
	gc = NULL;
}

void	*gcollector(size_t size, int mode)
{
	static t_gc	*gc;
	t_gc		*node;
	void		*data;

	if (mode)
	{
		data = malloc(size);
		if (!data)
			return (clear_gc(&gc), exit(1), NULL);
		node = malloc(sizeof(t_gc));
		if (!node)
			return (clear_gc(&gc), free(data), NULL);
		node->content = data;
		node->next = gc;
		gc = node;
		return (data);
	}
	else
		return (clear_gc(&gc), NULL);
}
