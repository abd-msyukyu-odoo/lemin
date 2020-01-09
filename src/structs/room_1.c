/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int				room_refill_tube(void *receiver, void *sent)
{
	return (ft_memanager_refill((t_memanager*)receiver, *(t_tube**)sent));
}

void					room_refill(t_room *room)
{
	ft_array_iteration(g_lemin->mmng, (t_array*)&room->a_tubes,
		room_refill_tube);
	ft_marray_empty(&room->a_tubes);
	ft_memanager_refill(g_lemin->mmng, room->key.key);
	ft_memanager_refill(g_lemin->mmng, room);
}

static t_room			*room_initialize(char *key, unsigned int status)
{
	t_room				*out;

	out = (t_room*)ft_typemanager_get(g_lemin->rooms_tmng,
		&g_lemin->rooms_used);
	if (!out)
		lemin_error(LEMIN_ERR_MEM);
	out->status = status;
	out->key = (t_charkey){key};
	if (!key || !ft_marray_initialize(&out->a_tubes, g_lemin->mmng,
		LEMIN_ROOM_ARRAY_TUBE_SIZE, sizeof(t_tube*)))
		lemin_error(LEMIN_ERR_MEM);
	out->weight = 0;
	out->visited = FALSE;
	out->isset = FALSE;
	return (out);
}

t_room					*room_firewall_initialize(char *key,
	unsigned int status)
{
	t_room				*out;
	t_charkey			charkey;

	charkey.key = lemin_append_status(key, status);
	out = NULL;
	if (!ft_hmap_contains_key((t_hmap*)&g_lemin->hm_rooms, &charkey,
		room_equals))
	{
		out = room_initialize(charkey.key, status);
		if (!ft_mhmap_add(&g_lemin->hm_rooms, out))
			lemin_error(LEMIN_ERR_MEM);
	}
	else
		ft_memanager_refill(g_lemin->mmng, charkey.key);
	return (out);
}
