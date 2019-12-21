/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_roads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_path		*cr_find_other(t_path *path)
{
	t_path			*road;
	t_step			*cur;

	road = lemin->paths->first;
	while (road)
	{
		if (road == path)
			road = road->next;
		cur = road->first;
		while (cur)
		{
			if (cur->room == path->cur->room)
			{
				road->cur = cur;
				return (road);
			}
			cur = cur->next;
		}
		road = road->next;
	}
	return (NULL);
}

static void			cr_exchange(t_path *cur, t_path *other)
{
	t_step			*s1;
	t_step			*e1;
	t_step			*s2;
	t_step			*e2;

	s1 = cur->cur->prev;
	e1 = other->cur;
	s2 = e1->prev;
	tube_inverse(s1->next->tube);
	e2 = s1->next->next;
	path_extract_step(cur, e2->prev);
	while (s2->prev == e2->next)
	{
		tube_inverse(e2->tube);
		e2 = e2->next;
		s2 = s2->prev;
		path_extract_step(cur, e2->prev);
		path_extract_step(other, s2->next);
	}
	s2 = s2->prev;
	path_extract_step(other, s2->next);
	s1->next = e1;
	e1->prev = s1;
	s2->next = e2;
	e2->prev = s2;
}

void				check_roads(void)
{
	t_path			*cur;
	t_tube			*t;
	t_path			*other;

	cur = lemin->best_path;
	cur->cur = cur->first;
	while (cur->cur->next)
	{
		t = cur->cur->tube;
		if (t->cost == LEMIN_DIR_REVERSE)
		{
			if ((other = cr_find_other(cur)))
				cr_exchange(cur, other);
			else
				lemin_error(LEMIN_ERR_ALGO);
		}
		cur->cur = cur->cur->next;
	}
}
