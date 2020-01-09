/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_tube				*tube_initialize(t_room *room1, t_room *room2,
		int direction, int cost)
{
	t_tube			*out;

	out = (t_tube*)ft_typemanager_get(g_lemin->tubes_tmng,
		&g_lemin->tubes_used);
	if (!out)
		lemin_error(LEMIN_ERR_MEM);
	out->direction = direction;
	out->cost = cost;
	out->room1 = room1;
	out->room2 = room2;
	return (out);
}

int					tube_equals(void *o1, void *o2)
{
	t_tube			*t1;
	t_tube			*t2;

	t1 = (t_tube*)o1;
	t2 = (t_tube*)o2;
	if ((room_equals(t1->room1, t2->room1) &&
			room_equals(t1->room2, t2->room2)) ||
		(room_equals(t1->room2, t2->room1) &&
			room_equals(t1->room1, t2->room2)))
		return (1);
	return (0);
}

void				tube_add_to_rooms(t_tube *tube)
{
	if (!ft_marray_add(&tube->room1->a_tubes, &tube) ||
		!ft_marray_add(&tube->room2->a_tubes, &tube))
		lemin_error(LEMIN_ERR_MEM);
}

void				tube_inverse(t_tube *tube)
{
	if (tube->direction == LEMIN_DIR_NATURAL)
		tube->direction = LEMIN_DIR_REVERSE;
	else if (tube->direction == LEMIN_DIR_REVERSE)
		tube->direction = LEMIN_DIR_NATURAL;
	tube->cost *= -1;
}
