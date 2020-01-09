/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path		*get_path_min_bridge(t_path *p)
{
	t_path			*min;

	min = p;
	while ((p = p->next))
		if (p->size < min->size)
			min = p;
	return (min);
}

int					get_cost(void)
{
	t_path			*min;

	set_nb_ants();
	min = get_path_min_bridge(g_lemin->paths->first);
	return (min->n_ants + min->size);
}

static int			get_max_bridge(t_path *p)
{
	int				length;

	length = p->size;
	while ((p = p->next))
		if (p->size > length)
			length = p->size;
	return (length);
}

static void			set_nb_ants_while2(int *max, int *nb_ants, t_path **curr,
	int *nb_path)
{
	if (*nb_ants % *nb_path > 0)
		*max = (*nb_ants / *nb_path) + 1;
	else
		*max = *nb_ants / *nb_path;
	(*curr)->n_ants += *max;
	*nb_ants -= *max;
	(*nb_path)--;
	*curr = (*curr)->next;
}

void				set_nb_ants(void)
{
	int				max;
	t_path			*p;
	int				nb_ants;
	t_path			*curr;
	int				nb_path;

	nb_path = 0;
	p = g_lemin->paths->first;
	max = get_max_bridge(p);
	curr = p;
	nb_ants = g_lemin->n_ants;
	while (curr)
	{
		nb_path++;
		curr->n_ants = max - curr->size;
		nb_ants -= curr->n_ants;
		curr = curr->next;
	}
	curr = p;
	while (curr && nb_ants)
		set_nb_ants_while2(&max, &nb_ants, &curr, &nb_path);
}
