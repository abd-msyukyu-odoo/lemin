/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				update_path(int weight)
{
	if (g_lemin->end->isset == g_lemin->n_paths + 1 &&
		g_lemin->end->weight <= weight)
		return ;
	g_lemin->end->isset = g_lemin->n_paths + 1;
	g_lemin->end->weight = weight;
	if ((g_lemin->best_path = path_refill(g_lemin->best_path)) ||
		!(g_lemin->best_path = path_clone(g_lemin->working_path)))
		return (lemin_error(LEMIN_ERR_ALGO));
}

static void			last_dash_to_nul(char *s)
{
	s = ft_strrchr(s, '-');
	*s = '\0';
}

static void			remove_in_out(void)
{
	t_path			*path;
	t_step			*step;

	last_dash_to_nul(g_lemin->start->key.key);
	last_dash_to_nul(g_lemin->end->key.key);
	path = g_lemin->paths->first;
	while (path)
	{
		step = path->first->next;
		while (step->next)
		{
			last_dash_to_nul(step->room->key.key);
			if (step->next && step->next->next)
				step->next = step->next->next;
			step = step->next;
		}
		path = path->next;
	}
}

void				pop_best_paths(void)
{
	unsigned int	i;
	t_paths			*best;
	t_paths			*tmp;

	best = *(t_paths**)ft_array_get((t_array*)g_lemin->old_paths, 0);
	i = 1;
	while (i < g_lemin->old_paths->array.n_items)
	{
		tmp = *(t_paths**)ft_array_get((t_array*)g_lemin->old_paths, i);
		if (tmp->cost < best->cost)
		{
			best = tmp;
		}
		i++;
	}
	g_lemin->paths = best;
	remove_in_out();
}
