
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

t_p_elem		*path_refill_elems(t_p_elem *elem) //path_elem_free && free_p_elem
{
	if (elem->next)
		elem->next = path_refill_elems(elem->next);
	ft_memanager_refill(lemin->mmng, elem);
	return (NULL);
}

t_path			*path_refill_all(t_path *p) //remove_path
{
	if (p->next)
		p->next = path_refill_all(p->next);
	p->elems = path_refill_elems(p->elems);
	ft_memanager_refill(lemin->mmng, p);
	return (NULL);
}

void			path_elem_refill_pop(t_p_elem **elem) // path_elem_pop
{
	t_p_elem	*cur;

	cur = (*elem);
	if (!(*elem)->next)
	{
		ft_memanager_refill(lemin->mmng, *elem);
		*elem = NULL;
		return ;
	}
	while ((*elem)->next && (*elem)->next->next)
		(*elem) = (*elem)->next;
	ft_memanager_refill(lemin->mmng, (*elem)->next);
	(*elem)->next = NULL;
	*elem = cur;
}

void			p_elem_remove_first(t_p_elem **e) // remove_p_elem
{
	t_p_elem	*elem;

	elem = *e;
	if (*e)
		*e = elem->next;
	ft_memanager_refill(lemin->mmng, elem);
}

void			path_elem_add_end(t_p_elem **elem, t_room *room)
{
	t_p_elem	*end;
	t_p_elem	*curr;

	if (!(end = (t_p_elem *)ft_memanager_get(lemin->mmng, sizeof(t_p_elem))))
		return (lemin_error(LEMIN_ERR_MEM));
	end->room = room;
	end->next = NULL;
	end->tube = NULL;
	curr = *elem;
	if (!curr)
		*elem = end;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = end;
	}
}

t_p_elem		*path_elem_dup(t_p_elem *elem)
{
	t_p_elem	*new;

	if (!(new = (t_p_elem *)ft_memanager_get(lemin->mmng, sizeof(t_p_elem))))
	{
		lemin_error(LEMIN_ERR_MEM);
		return (NULL);
	}
	new->room = elem->room;
	new->tube = elem->tube;
	if (elem->next)
		new->next = path_elem_dup(elem->next);
	return (new);
}

t_path			*paths_dup(t_path *path)
{
	t_path		*new;

	if (!path)
		return (NULL);
	if (!(new = (t_path *)ft_memanager_get(lemin->mmng, sizeof(t_path))))
	{
		lemin_error(LEMIN_ERR_MEM);
		return (NULL);
	}
	new->n_ants = path->n_ants;
	new->n_elems = path->n_elems;
	new->next = NULL;
	if (path->elems)
		new->elems = path_elem_dup(path->elems);
	if (path->next)
		new->next = paths_dup(path->next);
	return new;
}

void			path_add_end(t_path **path, t_p_elem *element)
{
	t_path		*end;
	t_path		*curr;

	if (!(end = (t_path *)ft_memanager_get(lemin->mmng, sizeof(t_path))))
		return (lemin_error(LEMIN_ERR_MEM));
	end->elems = element;
	end->next = NULL;
	end->n_elems = 0;
	curr = *path;
	if (!curr)
		*path = end;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = end;
	}
}
