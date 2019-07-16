/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <dabeloos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/07/10 14:16:28 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	function ft_room_create_extrema
**
**	create a start or ending room
**
**	@input:	the key of the room
**	@input:	a pointer on the room binary tree
**	@input:	the status (start or end)
**	@input:	the coordinates
**	@out:	a pointer on the newly t_room
*/

static t_room			*ft_room_create_extrema(char *key, t_btree *bt_rooms,
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
	if (!extrema || !ft_btree_add(bt_rooms, (t_data*)extrema))
	{
		ft_room_free(extrema);
		return (NULL);
	}
	return (extrema);
}

/*
**	function ft_room_create_start
**
**	create an OUT starting room and add it to a binary tree
**
**	@input:	the string key of the room
**	@input:	a pointer on the room binary tree
**	@input:	the x coordinate
**	@input:	the y coordinate
**	@out:	a pointer on the newly created t_room
*/

t_room					*ft_room_create_start(char *key, t_btree *bt_rooms,
	int x, int y)
{
	return (ft_room_create_extrema(key, bt_rooms, 1, (t_coordinates){x, y}));
}

/*
**	function ft_room_create_end
**
**	create an IN ending room and add it to a binary tree
**
**	@input:	the string key of the room
**	@input:	a pointer on the room binary tree
**	@input:	the x coordinate
**	@input:	the y coordinate
**	@out:	a pointer on the newly created t_room
*/

t_room					*ft_room_create_end(char *key, t_btree *bt_rooms,
	int x, int y)
{
	return (ft_room_create_extrema(key, bt_rooms, 0, (t_coordinates){x, y}));
}

/*
**	function ft_room_create_pair
**
**	create the IN and OUT rooms corresponding to key and add them to a binary
**
**	@input:	the string key of the room
**	@input:	a pointer on the room binary tree
**	@input:	the x coordinate
**	@input:	the y coordinate
**	@out:	1 if success | 0 if failure
*/

int						ft_room_create_pair(char *key, t_btree *bt_rooms,
	int x, int y)
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
		!ft_btree_add(bt_rooms, (t_data*)in) ||
		!ft_btree_add(bt_rooms, (t_data*)out))
	{
		ft_btree_remove(bt_rooms, in->key.key);
		ft_tube_free(tube);
		ft_room_free(in);
		ft_room_free(out);
		return (0);
	}
	return (1);
}
