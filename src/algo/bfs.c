/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	top = current->a_tubes.array.n_items;
	d = 0;
	while (d < top)
	{
		bfs_recursive(tube_get_connection(
			*(t_tube**)ft_array_get((t_array*)&current->a_tubes, d), current),
			weight + 1);
		d++;
	}
	path_elem_refill_pop(&(lemin->working_path));
	current->visited = FALSE;
}

void			bfs(void)
{
	lemin->end->weight = -1;
	bfs_recursive(lemin->start, 0);
	if (!(lemin->best_path))
		lemin_error(LEMIN_ERR_DISJOINT);
}
