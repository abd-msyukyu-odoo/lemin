#include "lemin.h"

static void	 bfs_recursive(t_room *current, int weight)
{
	unsigned int	top;
	unsigned int	d;

	if (current == lemin->end)
		return update_path(weight);
	if (current->visited == TRUE || current->weight <= weight || !(lemin->end->weight < 0 || weight <= lemin->end->weight))
		return ;
	current->weight = weight;
	current->visited = TRUE;
	path_elem_add_end(&(lemin->working_path), current);
	top = current->a_tubes->n_items;
	d = 0;
	while (d < top)
	{
		bfs_recursive(
				ft_tube_get_connection(
						ft_marray_get(current->a_tubes, d), current), weight + 1);
		d++;
	}
	path_elem_pop(&(lemin->working_path));
	current->visited = FALSE;
}

void			bfs()
{
	lemin->end->weight = -1;
	bfs_recursive(lemin->start, 0);
	if (!(lemin->best_path))
		lemin_error(LEM_ERR_DISJOINT);
}