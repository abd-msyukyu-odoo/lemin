/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 10:06:39 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/16 10:06:40 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	function ft_room_free
**
**	free the t_room instance
**
**	@input:	a pointer on the t_room to free
**	@out:	/
*/

void					ft_room_free(t_room *room)
{
	int					i;

	if (!room)
		return ;
	i = room->a_tubes->n_items;
	while (i-- > 0)
		ft_tube_free((t_tube*)ft_array_get(room->a_tubes, i));
	ft_array_free(room->a_tubes);
	ft_btree_free(room->bt_tubes);
	free(room->key.key);
	free(room);
}

/*
**	function ft_room_construct
**
**	create a t_room instance
**
**	@input:	the malloced string for the name
**	@input:	the status of the room
**	@input:	the x coordinate
**	@input:	the y coordinate
**	@out:	a pointer on the newly created t_room || NULL if fail
*/

t_room					*ft_room_construct(char *key, unsigned int status,
	int x, int y)
{
	t_room				*out;

	out = (t_room*)malloc(sizeof(t_room));
	if (!out)
		return (NULL);
	out->a_tubes = ft_array_construct(0);
	out->bt_tubes = ft_btree_construct(NULL);
	out->status = status;
	out->key = (t_data){key};
	if (!key || !out->a_tubes || !out->bt_tubes)
	{
		ft_room_free(out);
		return (NULL);
	}
	out->pos = (t_coordinates){x, y};
	return (out);
}

/*
**	function ft_room_create_tube_oriented
**
**	create and add a tube from "OUT" to "IN" rooms
**
**	@input:	a pointer on the out t_room
**	@input:	a pointer on the in t_room
**	@out:	an int depending on the success of the creation
*/

int						ft_room_create_tube_oriented(t_room *out, t_room *in)
{
	t_tube				*tube;

	tube = ft_tube_construct(out, in, 1, 1);
	if (!tube || !ft_tube_add_to_rooms(tube))
	{
		ft_tube_free(tube);
		return (0);
	}
	return (1);
}

/*
**	function
**
**	create and add a pair of tube, one from key1 relative "OUT" room to
**	key2 relative "IN" room, and another from key2 relative "OUT" room to
**	key1 relative "OUT" room
**
**	@input:	the first key
**	@input:	the second key
**	@input:	a pointer on the t_room b_tree
**	@out:	1 if success || 0 if error || -1 if nothing done
*/

int						ft_room_create_tube_pair(char *key1, char *key2,
	t_btree *bt_rooms)
{
	t_room				*in;
	t_room				*out;
	char				*key;
	int					result;

	result = -1;
	if (!(key = ft_strjoin(key1, IN)))
		return (0);
	in = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	if (!(key = ft_strjoin(key2, OUT)))
		return (0);
	out = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	if (in && out)
		result = ft_room_create_tube_oriented(out, in);
	if (!result || !(key = ft_strjoin(key2, IN)))
		return (0);
	in = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	if (!(key = ft_strjoin(key1, OUT)))
		return (0);
	out = (t_room*)ft_btree_get_data(bt_rooms, key);
	free(key);
	return ((in && out) ? ft_room_create_tube_oriented(out, in) : result);
}
