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

void					room_refill_tubes(t_room *room)
{
	ft_mhmap_empty(&room->hm_tubes);
}

void					room_refill(t_room *room)
{
	ft_mhmap_free(&room->hm_tubes);
	ft_memanager_refill(lemin->mmng, room->key.key);
	ft_memanager_refill(lemin->mmng, room);
}

t_room					*room_initialize(char *key, unsigned int status)
{
	t_room				*out;

	out = (t_room*)ft_marray_inject(&lemin->a_rooms);
	if (!out)
		lemin_error(LEMIN_ERR_MEM);
	out->status = status;
	out->key = (t_charkey){key};
	if (!key || !ft_mhmap_initialize(&out->hm_tubes, lemin->mmng, 8,
		ft_hmap_hash_addr))
		lemin_error(LEMIN_ERR_MEM);
	if (!ft_mhmap_add(&lemin->hm_rooms, out))
		lemin_error(LEMIN_ERR_MEM);
	return (out);
}

static char				*lemin_append_status(char *key, int status)
{
	size_t		l;
	char		*out;

	l = (key == NULL) ? 0 : ft_strlen(key);
	out = ft_memanager_get(lemin->mmng, sizeof(char) * (l + 3));
	if (!out)
		lemin_error(LEMIN_ERR_MEM);
	ft_memmove(out, key, l);
	ft_memmove(out + l, status_str(status), 2);
	out[l + 2] = '\0';
	return (out);
}

int						room_equals(void *o1, void *o2)
{
	return (!ft_strcmp(((t_room*)o1)->key.key, ((t_room*)o2)->key.key));
}

static t_room			*get_room_status(char *key, int status)
{
	t_room				*output;
	t_charkey			ckey;

	ckey.key = (status > -1) ? lemin_append_status(key, status) : key;
	output = ft_hmap_get((t_hmap*)&lemin->hm_rooms, &ckey, room_equals);
	ft_memanager_refill(lemin->mmng, ckey.key);
	return (output);
}

t_room					*get_room(char *key)
{
	t_charkey			ckey;

	ckey.key = key;
	return (ft_hmap_get((t_hmap*)&lemin->hm_rooms, &ckey, room_equals));
}

static int				room_is_connected_iteration(void *receiver, void *sent)
{
	t_tube				*t;
	t_room_wrapper		*wrapper;

	t = (t_tube*)sent;
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
	ft_hmap_bnode_iteration(&wrapper, (t_hmap*)&r1->hm_tubes,
		room_is_connected_iteration);
	return (wrapper.tube);
}

int						room_create_tube_pair(char *key1, char *key2)
{
	t_room				*in;
	t_room				*out;
	int					output;

	in = get_room_status(key1, LEMIN_IN);
	out = get_room_status(key2, LEMIN_OUT);
	output = 0;
	if (in && out && !room_get_connection(out, in))
	{
		tube_add_to_rooms(tube_initialize(out, in, LEMIN_DIR_NATURAL, 1));
		output |= 1;
	}
	in = get_room_status(key2, LEMIN_IN);
	out = get_room_status(key1, LEMIN_OUT);
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
	if (!ft_hmap_contains_key((t_hmap*)&lemin->hm_rooms, charkey.key, room_equals))
		out = room_initialize(charkey.key, status);
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

t_room					*room_create_start(char *key)
{
	lemin->start = room_create_extrema(key, LEMIN_OUT);
	return (lemin->start);
}

t_room					*room_create_end(char *key)
{
	lemin->end = room_create_extrema(key, LEMIN_IN);
	return (lemin->end);
}

int						room_create_pair(char *key)
{
	t_room				*in;
	t_room				*out;

	in = room_firewall_initialize(key, LEMIN_IN);
	out = room_firewall_initialize(key, LEMIN_OUT);
	if (!in || !out || room_get_connection(in, out))
		return (0);
	tube_add_to_rooms(tube_initialize(in, out, LEMIN_DIR_NATURAL, 0));
	return (1);
}
