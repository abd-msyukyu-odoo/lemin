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

t_path		*remove_path(t_path *p)
{
	if (p->next)
		p->next = remove_path(p->next);
	p->elements = free_p_elem(p->elements);
	free(p);
	return (NULL);
}

void		add_path(void *s, int nba, t_p_elem *elems)
{
	t_global	*g;
	t_path		*p;

	g = (t_global *)s;
	if (!(p = (t_path *)malloc(sizeof(t_path))))
		print(destroy_global(g));
	p->nb_ants = nba;
	p->next = g->paths;
	g->paths = p;
	p->elements = elems;
}



///// ADDED

void        path_elem_pop(s_p_elem **elem)
{
	s_p_elem    *curr;

	curr = *elem;
	if (!(curr->next))
		return path_elem_free(elem);
	while ((*elem)->next && (*elem)->next->next)
	{
		(*elem) = (*elem)->next;
	}
	path_elem_free(&((*elem)->next))
}

void        path_elem_add_end(s_p_elem **elem, t_room *room)
{
	s_p_elem    *end;
	s_p_elem    *curr;

	//end = //mem_alloc
	end->room = room;
	end->next = NULL;
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

void        path_elem_free(s_p_elem **elem)
{
	// TODO mem_free///
	*elem = NULL;
}

s_path      *path_dup(s_path *path)
{
	t_path  *new;

	if (!path)
		return (NULL);
	// TODO MALLOCC
	// new =
	new->nb_ants = path->nb_ants;
	new->nb_elements = path->nb_elements;
	new->next = NULL;
	if (path->elements)
		new->elements = path_elem_dup(paths->elements);
	return new;
}

s_p_elem    *path_elem_dup(t_p_elem *elem)
{
	t_p_elem    *new;

	// TODO MALLOC
	new->room = elem->room;
	if (elem->next)
		new->next = path_elem_dup(elem->next);
	return (new);
}