/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void				initialize_paths(void)
{
	if (!(g_lemin->working_path = (t_path *)ft_memanager_get(g_lemin->mmng,
		sizeof(t_path))))
		lemin_error(LEMIN_ERR_MEM);
	g_lemin->best_path = NULL;
	if (!(g_lemin->paths = (t_paths *)ft_memanager_get(g_lemin->mmng,
		sizeof(t_paths))))
		lemin_error(LEMIN_ERR_MEM);
	if (!(g_lemin->old_paths = ft_marray_construct(g_lemin->mmng, 16,
		sizeof(t_paths*))))
		lemin_error(LEMIN_ERR_MEM);
	g_lemin->working_path->first = NULL;
	g_lemin->working_path->last = NULL;
	g_lemin->paths->first = NULL;
	g_lemin->paths->last = NULL;
}

static unsigned int		first_iteration(void)
{
	initialize_paths();
	bfs();
	algo_add_tubes_to_best_path();
	algo_add_best_path_to_paths();
	set_n_elems();
	set_negatives();
	g_lemin->n_paths = 1;
	return ((g_lemin->start->a_tubes.array.n_items <
		g_lemin->end->a_tubes.array.n_items) ?
		g_lemin->start->a_tubes.array.n_items :
		g_lemin->end->a_tubes.array.n_items);
}

void					algo(void)
{
	unsigned int		limit;

	limit = first_iteration();
	algo_add_paths_to_old_paths(get_cost());
	while (g_lemin->n_paths < limit)
	{
		bmf();
		if (!g_lemin->best_path)
			break ;
		algo_add_tubes_to_best_path();
		algo_add_best_path_to_paths();
		check_roads();
		set_n_elems();
		algo_add_paths_to_old_paths(get_cost());
		g_lemin->n_paths++;
	}
	pop_best_paths();
}
