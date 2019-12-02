
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
	path_elem_free(&(lemin->best_path)); // TODO path_elem function
	path_duplicate(lemin->working_path, &(lemin->best_path));
}

void    bmf_recursive(t_room *current, int weight)
{
	unsigned int    top;
	unsigned int    d;

	if (current == lemin->end)
		return bfs_update_path(weight + 1);
	if (current->visited == TRUE || current->weight <= weight || weight <= lemin->end->weight)
		return ;
	current->weight = weight;
	current->visited = TRUE;
	path_elem_add_end(lemin->working_path, current); // TODO path function
	top = current->a_tubes->n_items;
	d = 0;
	while (d < top)
	{
		bmf_recursive(
				ft_tube_get_connection(
						ft_array_get(current->a_tubes, d), current), weight + 1);
		d++;
	}
	path_elem_pop(lemin->working_path); // TODO path function
	current->visited = FALSE;
}

void    bfs()
{
	unsigned int    i;
	t_room          *start;
	bfs_recursive(start, 0);
	if (!(lemin->best_path))
		lemin_error();

}