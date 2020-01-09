/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				algo_add_tubes_to_best_path(void)
{
	t_step			*elem;

	path_append(g_lemin->best_path, g_lemin->end);
	elem = g_lemin->best_path->first;
	while (elem->next)
	{
		if (!(elem->tube = room_get_connection(elem->room, elem->next->room)))
			lemin_error(LEMIN_ERR_MEM);
		elem = elem->next;
	}
}

void				algo_add_best_path_to_paths(void)
{
	paths_append(g_lemin->paths, g_lemin->best_path);
	g_lemin->best_path = NULL;
}

void				algo_add_paths_to_old_paths(int cost)
{
	t_paths			*paths;

	if (!(paths = paths_clone(g_lemin->paths)) ||
		!(paths->cost = cost) ||
		!(ft_marray_add(g_lemin->old_paths, &paths)))
		lemin_error(LEMIN_ERR_MEM);
}

void				set_negatives(void)
{
	t_path			*path;
	t_step			*step;

	path = g_lemin->paths->first;
	while (path)
	{
		step = path->first;
		while (step->next)
		{
			tube_inverse(step->tube);
			step = step->next;
		}
		path = path->next;
	}
}

void				set_n_elems(void)
{
	t_path			*path;
	t_step			*step;

	path = g_lemin->paths->first;
	while (path)
	{
		path->size = 0;
		step = path->first;
		while (step)
		{
			(path->size)++;
			step = step->next;
		}
		path->size /= 2;
		path = path->next;
	}
}
