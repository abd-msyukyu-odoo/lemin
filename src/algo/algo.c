
#include "lemin.h"

void	update_path(int weight)
{
	if (lemin->end->weight < weight)
		return ;
	lemin->end->weight = weight;
	path_elem_free(&(lemin->best_path));
	path_duplicate(lemin->working_path, &(lemin->best_path));
}

static void		algo_add_best_path_to_paths()
{
	t_p_elem	*elem;

	elem = lemin->best_path;
	while (elem->next)
	{
		if (!(elem->tube = ft_room_get_tube(elem->room, elem->next->room)))
			return (lemin_error(LEM_ERR_MEM));
		elem = elem->next;
	}
	path_add_end(&(lemin->paths), lemin->best_path);
	lemin->best_path = NULL;
}

static void		algo_add_paths_to_old_paths()
{
	if (ft_array_add(lemin->old_paths, (void *)paths_dup(lemin->paths)) != 1)
		lemin_error(LEMIN_ERR_ARRAY);
}

void			set_negatives()
{
	t_path		*paths;
	t_p_elem	elem;

	paths = lemin->paths;
	while (paths)
	{
		elem = path->elements;
		while(elem)
		{
			elem->tube->cost = -1;
			elem = elem->next;
		}
		paths = paths->next;
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
	algo_add_paths_to_old_paths();
	nb_paths = 1;
	while (nb_paths <= limit)
	{
		set_negatives();
		bmf();
		check_roads(); // TODO check
		algo_add_best_path_to_paths();
		// TODO count length
		cost(); // TODO check
		algo_add_paths_to_old_paths();
		nb_paths++;
	}

}