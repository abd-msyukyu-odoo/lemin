/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int						room_equals(void *o1, void *o2)
{
	return (!ft_strcmp(((t_charkey*)o1)->key, ((t_charkey*)o2)->key));
}

static int				room_is_connected_iteration(void *receiver, void *sent)
{
	t_tube				*t;
	t_room_wrapper		*wrapper;

	t = *(t_tube**)sent;
	wrapper = (t_room_wrapper*)receiver;
	if (wrapper->r1 == tube_get_connection(t, wrapper->r2))
	{
		wrapper->tube = t;
		return (0);
	}
	return (1);
}

t_tube					*room_get_connection(t_room *r1, t_room *r2)
{
	t_room_wrapper		wrapper;

	wrapper.r1 = r1;
	wrapper.r2 = r2;
	wrapper.tube = NULL;
	ft_array_iteration(&wrapper, (t_array*)&r1->a_tubes,
		room_is_connected_iteration);
	return (wrapper.tube);
}

static int				room_create_tube(char *key1, char *key2)
{
	t_room				*in;
	t_room				*out;

	in = room_get_status(key1, LEMIN_IN);
	out = room_get_status(key2, LEMIN_OUT);
	if (in && out)
	{
		if (!room_get_connection(out, in))
			tube_add_to_rooms(tube_initialize(out, in, LEMIN_DIR_NATURAL, 1));
		return (1);
	}
	return (0);
}

int						room_create_tube_pair(char *key1, char *key2)
{
	int					output;

	output = room_create_tube(key1, key2);
	output |= room_create_tube(key2, key1);
	return (output);
}
