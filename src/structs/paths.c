/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/14 17:32:05 by pierre            #+#    #+#             */
/*   Updated: 2019/07/15 08:19:09 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		paths_clone_initialize(t_paths *other)
{
	other->last = NULL;
	other->first = NULL;
}

t_paths			*paths_clone(t_paths *paths)
{
	t_paths		*other;
	t_path		*step;
	t_path		*cur;

	if (!(other = (t_paths*)ft_memanager_get(g_lemin->mmng, sizeof(t_paths))))
		lemin_error(LEMIN_ERR_MEM);
	paths_clone_initialize(other);
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
