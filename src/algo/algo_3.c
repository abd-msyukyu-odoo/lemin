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
	if (lemin->end->isset == lemin->n_paths + 1 && lemin->end->weight <= weight)
		return;
	lemin->end->isset = lemin->n_paths + 1;
	lemin->end->weight = weight;
	if ((lemin->best_path = path_refill(lemin->best_path)) ||
		!(lemin->best_path = path_clone(lemin->working_path)))
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

	last_dash_to_nul(lemin->start->key.key);
	last_dash_to_nul(lemin->end->key.key);
	path = lemin->paths->first;
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

	best = *(t_paths**)ft_array_get((t_array*)lemin->old_paths, 0);
	i = 1;
	while (i < lemin->old_paths->array.n_items)
	{
		tmp = *(t_paths**)ft_array_get((t_array*)lemin->old_paths, i);
		if (tmp->cost < best->cost)
		{
			best = tmp;
		}
		i++;
	}
	lemin->paths = best;
	remove_in_out();
}
