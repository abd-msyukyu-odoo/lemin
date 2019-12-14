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

///// USED for printing

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



///// ADDED for BFS

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

t_p_elem    *path_elem_dup(t_p_elem *elem)
{
	t_p_elem    *new;

	if (!(new = (t_p_elem *)ft_memanager_get(lemin->mmmg, sizeof(t_p_elem))))
	{
		lemin_error(LEMIN_ERR_MEM);
		return (NULL);
	}
	new->room = elem->room;
	if (elem->next)
		new->next = path_elem_dup(elem->next);
	return (new);
}

void        path_elem_free(t_p_elem **elem)
{
	if (*elem == NULL)
		return ;
	if (ft_memanager_refill(lemin->mmng, (void *)*elem) != 1) // TODO ajuster chiffre
		return (lemin_error(LEMIN_ERR_MEM));
	*elem = NULL;
}

t_path      *paths_dup(t_path *path)
{
	t_path  *new;

	if (!path)
		return (NULL);
	if (!(new = (t_path *)ft_memanager_get(lemin->mmmg, sizeof(s_path))))
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

void        path_add_end(t_path **path, s_p_elem *element)
{
	t_elem  *end;
	t_elem  *curr;

	//end = //mem_alloc
	end->room = room;
	end->next = NULL;
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