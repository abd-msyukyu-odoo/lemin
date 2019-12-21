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
	path_refill(lemin->best_path);
	lemin->best_path = path_clone(lemin->working_path);
}

void            pop_best_paths()
{
	unsigned int        i;
	t_paths_with_cost   *best;
	t_paths_with_cost   *tmp;

	best = (t_paths_with_cost *)ft_marray_get(lemin->old_paths, 0);
	i = 1;
	while (i < lemin->old_paths->n_item)
	{
		tmp = (t_paths_with_cost *)ft_marray_get(lemin->old_paths, i);
		if (tmp->cost < best->cost)
			best = tmp;
		i++;
	}
	lemin->paths = best->paths;
}

static void		algo_add_best_path_to_paths()
{
	t_step		*elem;

	elem = lemin->best_path->first;
	while (elem->next)
	{
		if (!(elem->tube = room_get_connection(elem->room, elem->next->room)))
			lemin_error(LEMIN_ERR_MEM);
		elem = elem->next;
	}
	paths_append(lemin->paths, lemin->best_path);
	lemin->best_path = NULL;
}

//doit ajouter tous les chemins d'une solution dans un tableau ?
//(ne fait pas ca, a corriger)
/////////////////////////////////////////si, elle le fait:
static void		algo_add_paths_to_old_paths(int cost)
{
	t_paths     *paths;

	if (!(paths = paths_clone(lemin->paths)) ||// duplicata des paths d'une itération
		!(paths->cost = cost) ||// assugnation du cost d'un ensemble d'une itération
		!(ft_marray_add(lemin->old_paths, (void *)paths)))// ajout de l'élément à l'array
		lemin_error(LEMIN_ERR_MEM);
}

//reset le cout des rooms a -1 (a supprimer ?)
//////////////////////////////////////////////////non, c'est pas le cout des room, c'est le cout des chemins
// static void		set_negatives()
// {
// 	t_path		*paths;
// 	t_step		*elem;

// 	paths = lemin->paths->first;
// 	while (paths)
// 	{
// 		elem = paths->first;
// 		while(elem)
// 		{
// 			elem->tube->cost = -1;
// 			elem = elem->next;
// 		}
// 		paths = paths->next;
// 	}
// }

//sert a compter le nombre d'elements dans un path ?
//////////////////////////////////////////////////// oui :)
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
		path = path->next;
	}
}

void	algo(void)
{
	unsigned int	limit;

	if (lemin->start->a_tubes.array.n_items < lemin->end->a_tubes.array.n_items)
		limit = lemin->start->a_tubes.array.n_items;
	else
		limit = lemin->end->a_tubes.array.n_items;
	bfs();
	algo_add_best_path_to_paths();
	lemin->n_paths = 1;
	algo_add_paths_to_old_paths(get_cost(lemin->paths, (int)lemin->n_paths));
	while (lemin->n_paths <= limit)
	{
		//set_negatives(); a supprimer
		bmf();
		check_roads();
		algo_add_best_path_to_paths();
		set_n_elems();
		algo_add_paths_to_old_paths(get_cost(lemin->paths,
			(int)lemin->n_paths));
		lemin->n_paths++;
	}
	pop_best_paths();
}
