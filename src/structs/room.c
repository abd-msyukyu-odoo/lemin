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
	static char			**status_str = {"-I", "-O"};

	return (status_str[status % 2]);
}

void					room_refill_tubes(t_room *room)
{
	ft_mhmap_empty(&room->hm_tubes);
}

t_room					*room_initialize(char *key, unsigned int status)
{
	t_room				*out;

	out = (t_room*)ft_marray_inject(&lemin->a_rooms);
	if (!out)
		lemin_error(LEMIN_MEM_ERR);
	out->status = status;
	out->key = (t_charkey){key};
	if (!key || !ft_mhmap_initialize(&out->hm_tubes, lemin->mmng, 8,
		ft_hmap_hash_addr))
		lemin_error(LEMIN_MEM_ERR);
	return (out);
}

static char				*lemin_append_status(char *key, int status)
{
	size_t		l;
	char		*out;

	l = (key == NULL) ? 0 : ft_strlen(key);
	out = ft_memanager_get(lemin->mmng, sizeof(char) * (l + 3));
	if (!out)
		lemin_error(LEMIN_MEM_ERR);
	ft_memmove(out, key, l);
	ft_memmove(out + l, status_str(status), 2);
	out[l + 2] = '\0';
	return (out);
}

int						equals_room(void *o1, void *o2)
{
	return (!ft_strcmp(((t_room*)o1)->key.key, ((t_room*)o2)->key.key));
}

static t_room			*get_room_status(char *key, int status)
{
	t_room				*output;
	t_charkey			ckey;

	ckey.key = (status > -1) ? lemin_append_status(key, status) : key;
	output = ft_hmap_get(&lemin->hm_rooms, &ckey, equals_room);
	ft_memanager_refill(lemin->mmng, ckey.key);
	return (output);
}

t_room					*get_room(char *key)
{
	t_charkey			ckey;

	ckey.key = key;
	return (ft_hmap_get(&lemin->hm_rooms, &ckey, equals_room));
}

int						room_create_tube_pair(char *key1, char *key2)
{
	t_room				*in;
	t_room				*out;
	int					

	in = get_room_status(key1, LEMIN_IN);
	out = get_room_status(key2, LEMIN_OUT);
	if (in && out)
		tube_add_to_rooms(tube_initialize(out, in, 1, 1));
	in = get_room_status(key2, LEMIN_IN);
	out = get_room_status(key1, LEMIN_OUT);
	if (in && out)
		tube_add_to_rooms(tube_initialize(out, in, 1, 1));
}

static t_room			*room_create_extrema(char *key, t_btree *bt_rooms,
	unsigned int status, t_coordinates pos)
{
	t_room				*extrema;

	if (status)
		extrema = ft_room_construct(ft_strjoin(key, OUT), 1, pos.x, pos.y);
	else
		extrema = ft_room_construct(ft_strjoin(key, IN), 0, pos.x, pos.y);
	free(key);
	if (!extrema)
		return (NULL);
	if (!extrema || !ft_btree_add(bt_rooms, (t_charkey*)extrema))
	{
		ft_room_free(extrema);
		return (NULL);
	}
	return (extrema);
}

t_room					*room_create_start(char *key, t_btree *bt_rooms, int x, int y)
{
	return (ft_room_create_extrema(key, bt_rooms, 1, (t_coordinates){x, y}));
}

t_room					*room_create_end(char *key, t_btree *bt_rooms, int x, int y)
{
	return (ft_room_create_extrema(key, bt_rooms, 0, (t_coordinates){x, y}));
}

int						room_create_pair(char *key, t_btree *bt_rooms, int x, int y)
{
	t_room				*in;
	t_room				*out;
	t_tube				*tube;

	in = ft_room_construct(ft_strjoin(key, IN), 0, x, y);
	out = ft_room_construct(ft_strjoin(key, OUT), 1, x, y);
	free(key);
	if (!in || !out)
	{
		ft_room_free(in);
		return (0);
	}
	tube = ft_tube_construct(in, out, 1, 0);
	if (!tube || !ft_tube_add_to_rooms(tube) ||
		!ft_btree_add(bt_rooms, (t_charkey*)in) ||
		!ft_btree_add(bt_rooms, (t_charkey*)out))
	{
		ft_btree_remove(bt_rooms, in->key.key);
		ft_tube_free(tube);
		ft_room_free(in);
		ft_room_free(out);
		return (0);
	}
	return (1);
}
