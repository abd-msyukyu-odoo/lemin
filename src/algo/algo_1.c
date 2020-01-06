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
	if (!(lemin->working_path = (t_path *)ft_memanager_get(lemin->mmng,
		sizeof(t_path))))
		lemin_error(LEMIN_ERR_MEM); 
	lemin->best_path = NULL;
	if (!(lemin->paths = (t_paths *)ft_memanager_get(lemin->mmng,
		sizeof(t_paths))))
		lemin_error(LEMIN_ERR_MEM);
	if (!(lemin->old_paths = ft_marray_construct(lemin->mmng, 16,
		sizeof(t_paths*))))
		lemin_error(LEMIN_ERR_MEM);
	lemin->working_path->first = NULL;
	lemin->working_path->last = NULL;
	lemin->paths->first = NULL;
	lemin->paths->last = NULL;
}

static unsigned int		first_iteration(void)
{
	initialize_paths();
	bfs();
	algo_add_tubes_to_best_path();
	algo_add_best_path_to_paths();
	set_n_elems();
	set_negatives();
	lemin->n_paths = 1;
	return ((lemin->start->a_tubes.array.n_items <
		lemin->end->a_tubes.array.n_items) ?
		lemin->start->a_tubes.array.n_items :
		lemin->end->a_tubes.array.n_items);
}

void					algo(void)
{
	int					old_cost;
	int					cost;
	unsigned int		limit;

	limit = first_iteration();
	old_cost = get_cost();
	algo_add_paths_to_old_paths(old_cost);
	cost = -1;
	while (lemin->n_paths < limit && cost < old_cost)
	{
		if (cost != -1)
			old_cost = cost;
		bmf();
		if (!lemin->best_path)
			break ;
		algo_add_tubes_to_best_path();
		check_roads();
		algo_add_best_path_to_paths();
		set_n_elems();
		cost = get_cost();
		algo_add_paths_to_old_paths(cost);
		lemin->n_paths++;
	}
	pop_best_paths();
}
