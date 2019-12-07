
#include "lemin.h"

// dans algo.h
# define FALSE 0
# define TRUE 1
// dans print.h
# define LEM_ERR_DISJOINT -3
// TODO add error message no path found between start and end


void    bfs_update_path(int weight)
{
	if (lemin->end->weight < weight)
		return ;
	lemin->end->weight = weight;
	path_elem_free(&(lemin->best_path));
	path_duplicate(lemin->working_path, &(lemin->best_path));
}

void    bmf_recursive(t_room *current, int weight)
{
	unsigned int    top;
	unsigned int    d;

	if (current == lemin->end)
		return bfs_update_path(weight + 1);
	if (current->visited == TRUE || current->weight <= weight || lemin->end->weight < 0 || weight <= lemin->end->weight)
		return ;
	current->weight = weight;
	current->visited = TRUE;
	path_elem_add_end(&(lemin->working_path), current);
	top = current->a_tubes->n_items;
	d = 0;
	while (d < top)
	{
		bmf_recursive(
				ft_tube_get_connection(
						ft_array_get(current->a_tubes, d), current), weight + 1);
		d++;
	}
	path_elem_pop(&(lemin->working_path));
	current->visited = FALSE;
}

void    bfs()
{
	lemin->end->weight = -1;
	bfs_recursive(lemin->start, 0);
	if (!(lemin->best_path))
		lemin_error(LEM_ERR_DISJOINT);
}