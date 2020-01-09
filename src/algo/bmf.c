/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			bmf_recursive(t_room *current, int weight)
{
	unsigned int	top;
	unsigned int	d;
	t_tube			*t;

	if (!current)
		return ;
	if (current == g_lemin->end)
		return (update_path(weight));
	if (current->visited == 1 ||
		(g_lemin->n_paths < current->isset && current->weight <= weight))
		return ;
	current->weight = weight;
	current->isset = g_lemin->n_paths + 1;
	current->visited = TRUE;
	path_append(g_lemin->working_path, current);
	top = current->a_tubes.array.n_items;
	d = 0;
	while (d < top)
	{
		t = *(t_tube**)ft_array_get((t_array*)&current->a_tubes, d);
		bmf_recursive(tube_navigate(t, current), weight + t->cost);
		d++;
	}
	path_remove_last(g_lemin->working_path);
	current->visited = FALSE;
}

void				bmf(void)
{
	if (!g_lemin->working_path)
		return (lemin_error(LEMIN_ERR_MEM));
	bmf_recursive(g_lemin->start, 0);
}
