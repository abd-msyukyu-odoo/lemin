/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	update_path(int weight)
{
	if (lemin->end->weight < weight)
		return ;
	lemin->end->weight = weight;
	path_refill_elems(lemin->best_path);
	lemin->best_path = path_elem_dup(lemin->working_path);
}

static void		algo_add_best_path_to_paths()
{
	t_p_elem	*elem;

	elem = lemin->best_path;
	while (elem->next)
	{
		if (!(elem->tube = room_get_connection(elem->room, elem->next->room)))
			return (lemin_error(LEMIN_ERR_MEM));
		elem = elem->next;
	}
	path_add_end(&(lemin->paths), lemin->best_path);
	lemin->best_path = NULL;
}

static void		algo_add_paths_to_old_paths(int cost)
{
	t_paths_with_cost	*paths_with_cost;

	if (!(paths_with_cost = (t_paths_with_cost *)ft_memanager_get(lemin->mmng, sizeof(t_paths_with_cost))) ||
		!(paths_with_cost->path = paths_dup(lemin->paths)) ||
		!(paths_with_cost->cost = cost) ||
		!(ft_marray_add(lemin->old_paths, paths_with_cost)))
		lemin_error(LEMIN_ERR_MEM);
}

static void		set_negatives()
{
	t_path		*paths;
	t_p_elem	*elem;

	paths = lemin->paths;
	while (paths)
	{
		elem = paths->elems;
		while(elem)
		{
			elem->tube->cost = -1;
			elem = elem->next;
		}
		paths = paths->next;
	}
}

static void		set_n_elems()
{
	t_path		*path;
	t_p_elem	*elem;

	path = lemin->paths;
	while (path)
	{
		path->n_elems = 0;
		elem = path->elems;
		while (elem)
		{
			(path->n_elems)++;
			elem = elem->next;
		}
		path = path->next;
	}
}

void	algo(void)
{
	unsigned int	limit;
	unsigned int	n_paths;

	if (lemin->start->a_tubes.array.n_items < lemin->end->a_tubes.array.n_items)
		limit = lemin->start->a_tubes.array.n_items;
	else
		limit = lemin->end->a_tubes.array.n_items;
	bfs();
	algo_add_best_path_to_paths();
	n_paths = 1;
	algo_add_paths_to_old_paths(get_cost(lemin->paths, (int)n_paths));
	while (n_paths <= limit)
	{
		set_negatives();
		bmf();
		check_roads();
		algo_add_best_path_to_paths();
		set_n_elems();
		algo_add_paths_to_old_paths(get_cost(lemin->paths, (int)n_paths));
		n_paths++;
	}

}
