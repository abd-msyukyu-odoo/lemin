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

t_path			*path_refill(t_path *path)
{
	t_step		*cur;
	t_step		*next;

	if (!path)
		return (NULL);
	cur = path->first;
	while (cur)
	{
		next = cur->next;
		ft_memanager_refill(g_lemin->mmng, cur);
		cur = next;
	}
	ft_memanager_refill(g_lemin->mmng, path);
	return (NULL);
}

void			path_remove_last(t_path *path)
{
	t_step		*cur;

	if (!path->first)
		return ;
	else if (path->last == path->first)
	{
		ft_memanager_refill(g_lemin->mmng, path->first);
		path->last = NULL;
		path->first = NULL;
		return ;
	}
	cur = path->last;
	path->last = cur->prev;
	path->last->next = NULL;
	ft_memanager_refill(g_lemin->mmng, cur);
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
	ft_memanager_refill(g_lemin->mmng, step);
}

void			path_append(t_path *path, t_room *room)
{
	t_step		*step;

	if (!(step = (t_step*)ft_memanager_get(g_lemin->mmng, sizeof(t_step))))
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

	if (!(other = (t_path*)ft_memanager_get(g_lemin->mmng, sizeof(t_path))))
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
