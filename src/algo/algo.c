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
	if (lemin->end->isset == lemin->n_paths + 1 && lemin->end->weight < weight)
		return;
	lemin->end->isset = lemin->n_paths + 1;
	lemin->end->weight = weight;
	if ((lemin->best_path = path_refill(lemin->best_path)) ||
		!(lemin->best_path = path_clone(lemin->working_path)))
		return lemin_error(LEMIN_ERR_ALGO);
}

void            pop_best_paths(void)
{
	unsigned int        i;
	t_paths             *best;
	t_paths             *tmp;

	best = *(t_paths**)ft_array_get((t_array*)lemin->old_paths, 0);
	printf("::: %d\n", best->cost);
	i = 1;
	while (i < lemin->old_paths->array.n_items)
	{
		tmp = *(t_paths**)ft_array_get((t_array*)lemin->old_paths, i);
		printf("::: %d\n", tmp->cost);
		if (tmp->cost < best->cost)
		{
			best = tmp;
		}
		i++;
	}
	lemin->paths = best;
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

//doit ajouter tous les chemins d'une solution dans un tableau ?
//(ne fait pas ca, a corriger)
/////////////////////////////////////////si, elle le fait:
static void		algo_add_paths_to_old_paths(int cost)
{
	t_paths     *paths;

	if (!(paths = paths_clone(lemin->paths)) ||// duplicata des paths d'une itération
		!(paths->cost = cost) ||// assugnation du cost d'un ensemble d'une itération
		!(ft_marray_add(lemin->old_paths, &paths)))// ajout de l'élément à l'array
		lemin_error(LEMIN_ERR_MEM);
}

////////////////////////////////////////////////non, c'est pas le cout des room, c'est le cout des chemins
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
		path->size /= 2;
		path = path->next;
	}
}

static void		initialize_paths(void)
{
	if (!(lemin->working_path = (t_path *)ft_memanager_get(lemin->mmng, sizeof(t_path))))
		lemin_error(LEMIN_ERR_MEM); 
	lemin->best_path = NULL;
	if (!(lemin->paths = (t_paths *)ft_memanager_get(lemin->mmng, sizeof(t_paths))))
		lemin_error(LEMIN_ERR_MEM);
	if (!(lemin->old_paths = ft_marray_construct(lemin->mmng, 16,
		sizeof(t_paths*))))
		lemin_error(LEMIN_ERR_MEM);
	lemin->working_path->first = NULL;
	lemin->working_path->last = NULL;
	lemin->paths->first = NULL;
	lemin->paths->last = NULL;
}

void	algo(void)
{
	unsigned int	limit;

	if (lemin->start->a_tubes.array.n_items < lemin->end->a_tubes.array.n_items)
		limit = lemin->start->a_tubes.array.n_items;
	else
		limit = lemin->end->a_tubes.array.n_items;
	initialize_paths();
	printf("- initialize paths done\n");
	bfs();
	printf("- bfs done\n");
	algo_add_tubes_to_best_path();
	algo_add_best_path_to_paths();
	set_n_elems();
	printf("- best path added to paths\n");
	set_negatives();
	printf("- negatives setted\n");
	lemin->n_paths = 1;
	algo_add_paths_to_old_paths(get_cost());
	printf("- paths added to olds paths\n");
	while (lemin->n_paths < limit)
	{
		printf("- while iteration nb %d\n", lemin->n_paths);
		bmf();
		printf("- - bmf done\n");
		if (!lemin->best_path)
			break ;
		algo_add_tubes_to_best_path();
		check_roads();
		printf("- - bmf done\n");
		algo_add_best_path_to_paths();
		printf("- - bmf done\n");
		set_n_elems();
		algo_add_paths_to_old_paths(get_cost());
		lemin->n_paths++;
	}
	printf("- while done\n");
	printf_old_paths();
	pop_best_paths();
	printf("- pop best paths\n");
	//set_nb_ants();
	printf("- bn_ants per path done\n");
	printf_paths();
}
