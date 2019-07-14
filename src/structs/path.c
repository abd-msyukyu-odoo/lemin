/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:32:05 by pierre            #+#    #+#             */
/*   Updated: 2019/07/14 17:55:45 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_p_elem	*free_p_elem(t_p_elem *elem)
{
	if (elem->next)
		elem->next = free_p_elem(elem->next);
	elem->key = NULL;
	free(elem);
	return (NULL);
}

t_p_elem	*add_t_p_elem(t_p_elem *elem, char *key)
{
	t_p_elem	*current;


	if (elem)
	{
		current = elem;
		while (current->next)
			current = current->next;
		if (!(current->next = (t_p_elem *)malloc(sizeof(t_p_elem))))
			return (free_p_elem(elem));
		current = current->next;
		current->next = NULL;
		current->key = key;
		return (elem);
	}
	if (!(elem = (t_p_elem *)malloc(sizeof(t_p_elem))))
		return (NULL);
	elem->next = NULL;
	elem->key = key;
	return (elem);
}

void		remove_path(t_path *p)
{
	if (p->next)
		remove_path(p->next);
	p->elements = free_p_elem(p->elements);
	free(p);
}

void		add_path(t_global *g, int nba, t_p_elem *elems)
{
	t_path	*p;

	if (!(p = (t_path *)malloc(sizeof(t_path))))
		print(destroy_t_global(g));
	p->nb_ants = nba;
	p->next = g->paths;
	g->paths = p;
	p->elements = elems;
}
