
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:32:05 by pierre            #+#    #+#             */
/*   Updated: 2019/07/15 08:19:09 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_p_elem		*path_refill_elems(t_p_elem *elem)
{
	if (elem->next)
		elem->next = path_refill_elems(elem->next);
	elem->key = NULL;
	ft_memanager_refill(lemin->mmng, elem);
	return (NULL);
}

t_p_elem		*p_elem_add(t_p_elem *elem, char *key)
{
	t_p_elem	*current;

	if (elem)
	{
		current = elem;
		while (current->next)
			current = current->next;
		if (!(current->next = (t_p_elem *)ft_memanager_get(lemin->mmng,
			sizeof(t_p_elem))))
			lemin_error(LEMIN_ERR_MEM);
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

t_path			*path_refill_all(t_path *p)
{
	if (p->next)
		p->next = path_refill_elems(p->next);
	p->elems = path_refill_elems(p->elems);
	ft_memanager_refill(lemin->mmng, p);
	return (NULL);
}

void			path_add_new(int n_ants, t_p_elem *elems)
{
	t_path		*p;

	if (!(p = (t_path*)ft_memanager_get(lemin->mmng, sizeof(t_path))))
		lemin_error(LEMIN_ERR_MEM);
	p->n_ants = n_ants;
	p->next = lemin->paths;
	p->elems = elems;
	lemin->paths = p;
}
