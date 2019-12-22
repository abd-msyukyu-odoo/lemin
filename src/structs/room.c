/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char				*status_str(int status)
{
	static char			*status_str[LEMIN_SIZE_SUFFIX] = {"-I", "-O"};

	return (status_str[status % 2]);
}

static int				room_refill_tube(void *receiver, void *sent)
{
	return (ft_memanager_refill((t_memanager*)receiver, *(t_tube**)sent));
}

void					room_refill(t_room *room)
{
	ft_array_iteration(lemin->mmng, (t_array*)&room->a_tubes, room_refill_tube);
	ft_marray_empty(&room->a_tubes);
	ft_memanager_refill(lemin->mmng, room->key.key);
	ft_memanager_refill(lemin->mmng, room);
}

t_room					*room_initialize(char *key, unsigned int status)
{
	t_room				*out;

	out = (t_room*)ft_typemanager_get(lemin->rooms_tmng, &lemin->rooms_used);
	if (!out)
		lemin_error(LEMIN_ERR_MEM);
	out->status = status;
	out->key = (t_charkey){key};
	if (!key || !ft_marray_initialize(&out->a_tubes, lemin->mmng,
		LEMIN_ROOM_ARRAY_TUBE_SIZE, sizeof(t_tube*)))
		lemin_error(LEMIN_ERR_MEM);
	out->weight = 0;
	out->visited = FALSE;
	out->isset = FALSE;
	return (out);
}

static char				*lemin_append_status(char *key, int status)
{
	size_t		l;
	char		*out;

	l = (key == NULL) ? 0 : ft_strlen(key);
	out = (char*)ft_memanager_get(lemin->mmng, sizeof(char) * (l + 3));
	if (!out)
		lemin_error(LEMIN_ERR_MEM);
	ft_memmove(out, key, l);
	ft_memmove(out + l, status_str(status), 2);
	out[l + 2] = '\0';
	return (out);
}

int						room_equals(void *o1, void *o2)
{
	return (!ft_strcmp(((t_charkey*)o1)->key, ((t_charkey*)o2)->key));
}

static t_room			*room_get_status(char *key, int status)
{
	t_room				*output;
	t_charkey			ckey;

	ckey.key = (status > -1) ? lemin_append_status(key, status) : key;
	output = ft_hmap_get((t_hmap*)&lemin->hm_rooms, &ckey, room_equals);
	ft_memanager_refill(lemin->mmng, ckey.key);
	return (output);
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

int						room_create_tube_pair(char *key1, char *key2)
{
	t_room				*in;
	t_room				*out;
	int					output;

	in = room_get_status(key1, LEMIN_IN);
	out = room_get_status(key2, LEMIN_OUT);
	output = 0;
	if (in && out && !room_get_connection(out, in))
	{
		tube_add_to_rooms(tube_initialize(out, in, LEMIN_DIR_NATURAL, 1));
		output |= 1;
	}
	in = room_get_status(key2, LEMIN_IN);
	out = room_get_status(key1, LEMIN_OUT);
	if (in && out && !room_get_connection(out, in))
	{
		tube_add_to_rooms(tube_initialize(out, in, LEMIN_DIR_NATURAL, 1));
		output |= 1;
	}
	return (output);
}

static t_room			*room_firewall_initialize(char *key,
	unsigned int status)
{
	t_room				*out;
	t_charkey			charkey;

	charkey.key = lemin_append_status(key, status);
	out = NULL;
	if (!ft_hmap_contains_key((t_hmap*)&lemin->hm_rooms, &charkey, room_equals))
	{
		out = room_initialize(charkey.key, status);
		if (!ft_mhmap_add(&lemin->hm_rooms, out))
			lemin_error(LEMIN_ERR_MEM);
	}
	else
		ft_memanager_refill(lemin->mmng, charkey.key);
	return (out);
}

static t_room			*room_create_extrema(char *key, unsigned int status)
{
	t_room				*extrema;

	extrema = NULL;
	if (status == LEMIN_OUT)
		extrema = room_firewall_initialize(key, LEMIN_OUT);
	else
		extrema = room_firewall_initialize(key, LEMIN_IN);
	return (extrema);
}

int						room_create_start(char *key)
{
	if (lemin->start)
		return (0);
	lemin->start = room_create_extrema(key, LEMIN_OUT);
	return (lemin->start != NULL);
}

int						room_create_end(char *key)
{
	if (lemin->end)
		return (0);
	lemin->end = room_create_extrema(key, LEMIN_IN);
	return (lemin->end != NULL);
}

int						room_create_pair(char *key)
{
	t_room				*in;
	t_room				*out;

	in = room_firewall_initialize(key, LEMIN_IN);
	out = room_firewall_initialize(key, LEMIN_OUT);
	if (!in || !out)
		return (0);
	tube_add_to_rooms(tube_initialize(in, out, LEMIN_DIR_NATURAL, 0));
	return (1);
}
