/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gcollector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-feng <oel-feng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 21:22:38 by asel-kha          #+#    #+#             */
/*   Updated: 2025/02/04 05:14:52 by oel-feng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

static t_memory	*create_node(void *ptr)
{
	t_memory	*new;

	new = malloc(sizeof(t_memory));
	if (!new)
		return (NULL);
	new->address = ptr;
	new->next = NULL;
	return (new);
}

static t_memory	*find_last(t_memory **head)
{
	t_memory	*current;

	current = *head;
	if (!head || !*head)
		return (NULL);
	while (current->next)
		current = current->next;
	return (current);
}

static void	lst_add_back(t_memory **head, t_memory *new)
{
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
		find_last(head)->next = new;
}

static void	free_memory(t_memory **head)
{
	t_memory	*current;
	t_memory	*next;

	current = *head;
	if (!head || !*head)
		return ;
	while (current)
	{
		next = current->next;
		if (current->address)
		{
			free(current->address);
			current->address = NULL;
		}
		free(current);
		current = next;
	}
	*head = NULL;
}

void	*gcollector(size_t size, int mode)
{
	static t_memory	*memory_list;
	t_memory		*tracker;
	void			*ptr;

	if (mode == 1)
	{
		ptr = malloc(size);
		if (!ptr)
		{
			free_memory(&memory_list);
			return (NULL);
		}
		tracker = create_node(ptr);
		if (!tracker)
		{
			free(ptr);
			free_memory(&memory_list);
			return (NULL);
		}
		lst_add_back(&memory_list, tracker);
		return (ptr);
	}
	else if (mode == 0)
		free_memory(&memory_list);
	return (NULL);
}
