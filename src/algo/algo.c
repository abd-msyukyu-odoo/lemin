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
	if (lemin->end->isset == lemin->n_paths + 1 && lemin->end->weight <= weight)
		return;
	lemin->end->isset = lemin->n_paths + 1;
	lemin->end->weight = weight;
	if ((lemin->best_path = path_refill(lemin->best_path)) ||
		!(lemin->best_path = path_clone(lemin->working_path)))
		return (lemin_error(LEMIN_ERR_ALGO));
}

static void		last_dash_to_nul(char *s)
{
	s = ft_strrchr(s, '-');
	*s = '\0';
}

void            remove_in_out(void)
{
	t_path      *path;
	t_step      *step;

	last_dash_to_nul(lemin->start->key.key);
	last_dash_to_nul(lemin->end->key.key);
	path = lemin->paths->first;
	while (path)
	{
		step = path->first->next;
		while (step->next)
		{
			last_dash_to_nul(step->room->key.key);
			if (step->next && step->next->next)
				step->next = step->next->next;
			step = step->next;
		}
		path = path->next;
	}
}

void            pop_best_paths(void)
{
	unsigned int        i;
	t_paths             *best;
	t_paths             *tmp;

	best = *(t_paths**)ft_array_get((t_array*)lemin->old_paths, 0);
	i = 1;
	while (i < lemin->old_paths->array.n_items)
	{
		tmp = *(t_paths**)ft_array_get((t_array*)lemin->old_paths, i);
		if (tmp->cost < best->cost)
		{
			best = tmp;
		}
		i++;
	}
	lemin->paths = best;
	remove_in_out();
}

static void		algo_add_tubes_to_best_path(void)
{
	t_step		*elem;

	path_append(lemin->best_path, lemin->end);
	elem = lemin->best_path->first;
	while (elem->next)
	{
		if (!(elem->tube = room_get_connection(elem->room, elem->next->room)))
			lemin_error(LEMIN_ERR_MEM);
		elem = elem->next;
	}
}

static void		algo_add_best_path_to_paths(void)
{
	paths_append(lemin->paths, lemin->best_path);
	lemin->best_path = NULL;
}

static void		algo_add_paths_to_old_paths(int cost)
{
	t_paths     *paths;

	if (!(paths = paths_clone(lemin->paths)) ||
		!(paths->cost = cost) ||
		!(ft_marray_add(lemin->old_paths, &paths)))
		lemin_error(LEMIN_ERR_MEM);
}

static void		set_negatives()
{
	t_path		*path;
	t_step		*step;

	path = lemin->paths->first;
	while (path)
	{
		step = path->first;
		while(step->next)
		{
			tube_inverse(step->tube);
			step = step->next;
		}
		path = path->next;
	}
}

static void		set_n_elems()
{
	t_path		*path;
	t_step		*step;

	path = lemin->paths->first;
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

static void		initialize_paths(void)
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

static unsigned int	set_limit(void)
{
	return ((lemin->start->a_tubes.array.n_items <
		lemin->end->a_tubes.array.n_items) ?
		lemin->start->a_tubes.array.n_items :
		lemin->end->a_tubes.array.n_items);
}

//void	algo(void)
//{
//	unsigned int	limit;
//
//	limit = set_limit();
//	initialize_paths();
//	bfs();
//	algo_add_tubes_to_best_path();
//	algo_add_best_path_to_paths();
//	set_n_elems();
//	set_negatives();
//	lemin->n_paths = 1;
//	algo_add_paths_to_old_paths(get_cost());
//	while (lemin->n_paths < limit)
//	{
//		bmf();
//		if (!lemin->best_path)
//			break ;
//		algo_add_tubes_to_best_path();
//		check_roads();
//		algo_add_best_path_to_paths();
//		set_n_elems();
//		algo_add_paths_to_old_paths(get_cost());
//		lemin->n_paths++;
//	}
//	pop_best_paths();
//}

void	algo(void)
{
	int             old_cost;
	int             cost;
	unsigned int	limit;

	limit = set_limit();
	initialize_paths();
	bfs();
	algo_add_tubes_to_best_path();
	algo_add_best_path_to_paths();
	set_n_elems();
	set_negatives();
	lemin->n_paths = 1;
	old_cost = get_cost();
	algo_add_paths_to_old_paths(old_cost);
	cost = -1;
	while (cost < old_cost)
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
