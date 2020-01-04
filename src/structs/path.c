
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

t_path			*path_refill(t_path *path) //path_elem_free && free_p_elem
{
	t_step		*cur;
	t_step		*next;

	if (!path)
		return (NULL);
	cur = path->first;
	while (cur)
	{
		next = cur->next;
		ft_memanager_refill(lemin->mmng, cur);
		cur = next;
	}
	ft_memanager_refill(lemin->mmng, path);
	return (NULL);
}

t_paths			*paths_refill(t_paths *paths) //remove_path
{
	t_path		*cur;
	t_path		*next;

	cur = paths->first;
	while (cur)
	{
		next = cur->next;
		path_refill(cur);
		cur = next;
	}
	ft_memanager_refill(lemin->mmng, paths);
	return (NULL);
}

void			path_remove_last(t_path *path) // path_elem_pop
{
	t_step		*cur;

	if (!path->first)
		return ;
	else if (path->last == path->first)
	{
		ft_memanager_refill(lemin->mmng, path->first);
		path->last = NULL;
		path->first = NULL;
		return ;
	}
	cur = path->last;
	path->last = cur->prev;
	path->last->next = NULL;
	ft_memanager_refill(lemin->mmng, cur);
}

void			path_extract_step(t_path *path, t_step *step)
{
	if (step->prev)
		step->prev->next = step->next;
	if (step->next)
		step->next->prev = step->prev;
	if (step == path->first)
	{
		path->first = step->next;
		path->first->prev = NULL;
	}
	if (step == path->last)
	{
		path->last = step->prev;
		path->last->next = NULL;
	}	
	ft_memanager_refill(lemin->mmng, step);
}

void			path_append(t_path *path, t_room *room)
{
	t_step		*step;

	if (!(step = (t_step*)ft_memanager_get(lemin->mmng, sizeof(t_step))))
		lemin_error(LEMIN_ERR_MEM);
	step->room = room;
	step->tube = NULL;
	step->next = NULL;
	step->prev = path->last;
	if (path->last)
		path->last->next = step;
	if (!path->first)
		path->first = step;
	path->last = step;
}

t_path			*path_clone(t_path *path)
{
	t_path		*other;
	t_step		*step;
	t_step		*cur;

	if (!(other = (t_path*)ft_memanager_get(lemin->mmng, sizeof(t_path))))
		lemin_error(LEMIN_ERR_MEM);
	other->first = NULL;
	other->last = NULL;
	other->next = NULL;
	other->prev = NULL;
	step = path->first;
	while (step)
	{
		path_append(other, step->room);
		if (!step->prev)
			cur = other->first;
		else
			cur = other->last;
		cur->tube = step->tube;
		step = step->next;
	}
	other->size = path->size;
	other->n_ants = path->n_ants;
	return (other);
}

t_paths			*paths_clone(t_paths *paths)
{
	t_paths		*other;
	t_path		*step;
	t_path		*cur;

	if (!(other = (t_paths*)ft_memanager_get(lemin->mmng, sizeof(t_paths))))
		lemin_error(LEMIN_ERR_MEM);
	other->last = NULL;
	other->first = NULL;
	step = paths->first;
	cur = NULL;
	while (step)
	{
		if (!cur)
		{
			other->first = path_clone(step);
			cur = other->first;
		}
		else
		{
			cur->next = path_clone(step);
			cur = cur->next;
		}
		step = step->next;
	}
	other->last = cur;
	return (other);
}

void			paths_append(t_paths *paths, t_path *path)
{
	path->next = NULL;
	path->prev = paths->last;
	if (paths->last)
		paths->last->next = path;
	if (!paths->first)
		paths->first = path;
	paths->last = path;
}