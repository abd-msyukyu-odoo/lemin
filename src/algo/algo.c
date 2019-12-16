
#include "lemin.h"

void	update_path(int weight)
{
	if (lemin->end->weight < weight)
		return ;
	lemin->end->weight = weight;
	path_elem_free(&(lemin->best_path));
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
		elem = paths->elements;
		while(elem)
		{
			elem->tube->cost = -1;
			elem = elem->next;
		}
		paths = paths->next;
	}
}

static void		set_nb_elements()
{
	t_path		*path;
	t_p_elem	*elem;

	path = lemin->paths;
	while (path)
	{
		path->nb_elements = 0;
		elem = path->elements;
		while (elem)
		{
			(path->nb_elements)++;
			elem = elem->next;
		}
		path = path->next;
	}
}

void	algo()
{
	unsigned int	limit;
	unsigned int	nb_paths;

	if (lemin->start->a_tubes->n_items < lemin->end->a_tubes->n_items)
		limit = lemin->start->a_tubes->n_items;
	else
		limit = lemin->end->a_tubes->n_items;
	bfs();
	algo_add_best_path_to_paths();
	nb_paths = 1;
	algo_add_paths_to_old_paths(get_cost(lemin->paths, (int)nb_paths));
	while (nb_paths <= limit)
	{
		set_negatives();
		bmf();
		check_roads();
		algo_add_best_path_to_paths();
		set_nb_elements();
		algo_add_paths_to_old_paths(get_cost(lemin->paths, (int)nb_paths));
		nb_paths++;
	}

}