
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





//new







//// used by printing
t_path		*remove_path(t_path *p)
{
	if (p->next)
		p->next = remove_path(p->next);
	p->elements = free_p_elem(p->elements);
	free(p);
	return (NULL);
}


///// ADDED for BFS

void		path_elem_pop(s_p_elem **elem)
{
	s_p_elem	*curr;

	curr = *elem;
	if (!(curr->next))
		return path_elem_free(elem);
	while ((*elem)->next && (*elem)->next->next)
	{
		(*elem) = (*elem)->next;
	}
	path_elem_free(&((*elem)->next))
}

void		path_elem_add_end(s_p_elem **elem, t_room *room)
{
	s_p_elem	*end;
	s_p_elem	*curr;

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

t_p_elem	*path_elem_dup(t_p_elem *elem)
{
	t_p_elem	*new;

	if (!(new = (t_p_elem *)ft_memanager_get(lemin->mmmg, sizeof(t_p_elem))))
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

void		path_elem_free(t_p_elem **elem)
{
	if (*elem == NULL)
		return ;
	if ((*elem)->next)
		path_elem_free(&((*elem)->next));
	if (ft_memanager_refill(lemin->mmng, (void *)*elem) != 1) // TODO ajuster chiffre
		return (lemin_error(LEMIN_ERR_MEM));
	*elem = NULL;
}

t_path	  *paths_dup(t_path *path)
{
	t_path  *new;

	if (!path)
		return (NULL);
	if (!(new = (t_path *)ft_memanager_get(lemin->mmng, sizeof(s_path))))
	{
		lemin_error(LEMIN_ERR_MEM);
		return (NULL);
	}
	new->nb_ants = path->nb_ants;
	new->nb_elements = path->nb_elements;
	new->next = NULL;
	if (path->elements)
		new->elements = path_elem_dup(paths->elements);
	if (path->next)
		new->next = paths_dup(path->next);
	return new;
}

void		path_add_end(t_path **path, t_p_elem *element)
{
	t_path		*end;
	t_path		*curr;

	if (!(end = (t_path *)ft_memanager_get(lemin->mmng, sizeof(s_path))))
		return (lemin_error(LEMIN_ERR_MEM));
	end->elements = element;
	end->next = NULL;
	end->nb_elements = 0;
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

void		remove_p_elem(t_p_elem **e)
{
	t_p_elem	*elem;

	elem = *e;
	*e = elem->next;
	elem->next = NULL;
	elem->
}
