/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   room.h											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dabeloos <dabeloos@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/06/28 20:59:04 by dabeloos		  #+#	#+#			 */
/*   Updated: 2019/07/10 14:14:21 by pierre		   ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H
# include <stdlib.h>
# include "btree.h"
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
**	room_1
**	4 functions
*/

void					ft_room_free(t_room *room);
t_room					*ft_room_construct(char *key, unsigned int status,
						int x, int y);
int						ft_room_create_tube_oriented(t_room *out, t_room *in);
int						ft_room_create_tube_pair(char *key1, char *key2,
							t_btree *bt_rooms);

/*
**	room_2
**	4 functions
*/

t_room					*ft_room_create_start(char *key, t_btree *bt_rooms,
	int x, int y);
t_room					*ft_room_create_end(char *key, t_btree *bt_rooms,
	int x, int y);
int						ft_room_create_pair(char *key, t_btree *bt_rooms,
	int x, int y);

#endif
