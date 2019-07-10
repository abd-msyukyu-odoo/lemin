/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <dabeloos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:59:04 by dabeloos          #+#    #+#             */
/*   Updated: 2019/07/10 14:14:21 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H
# include <stdlib.h>
# include "data.h"
# include "btree.h"
# include "array.h"
# include "libft.h"
# define IN "-IN"
# define OUT "-OUT"

/*
** x, y : ref-axis coordinates
*/
typedef struct			s_coordinates
{
	int					x;
	int					y;
}						t_coordinates;

/*
** key : contains the char *key which is the id of the t_room item
** bt_tubes : binary tree of tubes for search (has the same elements as a_tubes)
** a_tubes : array of tubes for iteration (has the same elements as bt_tubes)
** status :
** 	0 : "IN" room, as one that can only be entered from different "OUT"
** 	1 : "OUT" room, as one that can only be entered from the corresponding "IN"
** pos : x-y axis coordinates
*/
typedef struct			s_room
{
	t_data				key;
	t_btree				*bt_tubes;
	t_array				*a_tubes;
	unsigned int		status;
	t_coordinates		pos;
}						t_room;

/*
** free the t_room instance
*/
void					ft_room_free(t_room *room);

/*
** create a t_room instance
** return :
** 	t_room* : created instance
** 	NULL : error
*/
t_room					*ft_room_construct(char *key, unsigned int status, int x, int y);

/*
** create and add a tube from "OUT" to "IN" rooms
** return :
** 	1 : success
** 	0 : error
*/
int						ft_room_create_tube_oriented(t_room *out, t_room *in);

/*
** create and add a pair of tube, one from key1 relative "OUT" room to
** key2 relative "IN" room, and another from key2 relative "OUT" room to
** key1 relative "OUT" room
** return :
** 	1 : success
** 	0 : error
** -1 : no tube added
*/
int						ft_room_create_tube_pair(char *key1, char *key2,
							t_btree *bt_rooms);

/*
** create an OUT starting room and add it to a binary tree
** return :
** 	t_room* : created instance
** 	NULL : error
*/
t_room					*ft_room_create_start(char *key, t_btree *bt_rooms, int x, int y);

/*
** create an IN ending room and add it to a binary tree
** return :
** 	t_room* : created instance
** 	NULL : error
*/
t_room					*ft_room_create_end(char *key, t_btree *bt_rooms, int x, int y);

/*
** create the IN and OUT rooms corresponding to key and add them to a binary
** tree
** return :
** 	1 : success
** 	0 : error
*/
int						ft_room_create_pair(char *key, t_btree *bt_rooms, int x, int y);

#endif
