/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:59:04 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 20:59:05 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H
# include "libft.h"
# include "structs/charkey.h"
# define LEMIN_IN 0
# define LEMIN_OUT 1
# define LEMIN_SIZE_SUFFIX 3
# define LEMIN_ROOM_ARRAY_TUBE_SIZE 8

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
	t_charkey			key;
	t_marray			a_tubes;
	unsigned int		status;
	int					weight;
	int					visited;
	unsigned int		isset;
}						t_room;

/*
** room_1.c
**
** create a t_room instance if it does not already exist
** return :
** 	t_room* : created instance
** 	NULL : error
*/
t_room					*room_firewall_initialize(char *key,
	unsigned int status);

/*
** free the t_room instance
*/
void					room_refill(t_room *room);

/*
** room_2.c
**
** create an OUT starting room and add it to a binary tree
** return :
** 	t_room* : created instance
** 	NULL : error
*/
int						room_create_start(char *key);

/*
** create an IN ending room and add it to a binary tree
** return :
** 	t_room* : created instance
** 	NULL : error
*/
int						room_create_end(char *key);

/*
** create the IN and OUT rooms corresponding to key and add them to a binary
** tree
** return :
** 	1 : success
** 	0 : error
*/
int						room_create_pair(char *key);

/*
** room_3.c
*/
char					*lemin_append_status(char *key, int status);
t_room					*room_get_status(char *key, int status);

/*
** room_4.c
*/
int						room_equals(void *o1, void *o2);

/*
** create and add a pair of tube, one from key1 relative "OUT" room to
** key2 relative "IN" room, and another from key2 relative "OUT" room to
** key1 relative "OUT" room
** return :
** 	1 : success
** 	0 : error
** -1 : no tube added
*/
int						room_create_tube_pair(char *key1, char *key2);

#endif
