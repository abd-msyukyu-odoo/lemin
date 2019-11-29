/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
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

	out = (t_tube*)ft_marray_inject(&lemin->a_tubes);
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
	if ((equals_room(t1->room1, t2->room1) &&
			equals_room(t1->room2, t2->room2)) ||
		(equals_room(t1->room2, t2->room1) &&
			equals_room(t1->room1, t2->room2)))
		return (1);
	return (0);
}

void				tube_add_to_rooms(t_tube *tube)
{
	if (!ft_mhmap_add(&tube->room1->hm_tubes, tube) ||
		!ft_mhmap_add(&tube->room2->hm_tubes, tube))
		lemin_error(LEMIN_ERR_MEM);
}

t_room				*tube_get_connection(t_tube *tube, t_room *room)
{
	if (tube->room1 == room)
		return (tube->room2);
	else if (tube->room2 == room)
		return (tube->room1);
	else
		return (NULL);
}
