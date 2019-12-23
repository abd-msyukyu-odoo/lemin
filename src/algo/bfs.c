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

// pour moi devrait etre en iteratif (gere plus de rooms, gere les poids dans un
// ordre de type cercle avec rayon qui augmente a partir de la salle de debut)
// contrairement a la recursive qui va creuser le plus loin possible (spirale)
// avant de revenir en arriere (beaucoup de mise a jour de poids)
static void	 bfs_recursive(t_room *current, int weight)
{
	unsigned int	top;
	unsigned int	d;
	t_tube			*t;

	if (!current)
		return;
	if (current == lemin->end)
		return (update_path(weight));
	if (current->visited == 1 ||
		(current->isset && current->weight <= weight) ||
		(lemin->end->isset && weight > lemin->end->weight))
		return ;
	current->weight = weight;
	current->isset = 1;
	current->visited = 1;
	path_append(lemin->working_path, current);
	top = current->a_tubes.array.n_items;
	d = 0;
	while (d < top)
	{
		t = *(t_tube**)ft_array_get((t_array*)&current->a_tubes, d);
		bfs_recursive(tube_navigate(t, current), weight + t->cost);
		d++;
	}
	path_remove_last(lemin->working_path);
	current->visited = 0;
}

void			bfs(void)
{
	bfs_recursive(lemin->start, 0);
	if (!(lemin->best_path))
		lemin_error(LEMIN_ERR_DISJOINT);
}
