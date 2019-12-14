
#include "lemin.h"

void    bmf_recursive(t_room *current, int weight)
{
	unsigned int    top;
	unsigned int    d;
	t_tube          *t;

	if (current == lemin->end)
		return update_path(weight);
	if (current->visited == TRUE || current->weight <= weight)
		return ;
	current->weight = weight;
	current->visited = TRUE;
	path_elem_add_end(&(lemin->working_path), current);
	top = current->a_tubes->n_items;
	d = 0;
	while (d < top)
	{
		t = ft_tube_get_connection(ft_array_get(current->a_tubes, d), current);
		bmf_recursive(ft_tube_get_connection(t, weight + t->cost);
		d++;
	}
	path_elem_pop(&(lemin->working_path));
	current->visited = FALSE;
}

void    bellmand_ford()
{
	if (lemin->working_path)
		return (lemin_error(LEMIN_ERR_MEM));
	lemin->end->weight = -1;
	bmf_recursive(lemin->start, 0);
}