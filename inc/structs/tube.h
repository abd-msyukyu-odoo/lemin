/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:58:59 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 20:59:00 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUBE_H
# define TUBE_H
# include "structs/room.h"
# include "structs/charkey.h"
# define LEMIN_DIR_NATURAL 1
# define LEMIN_DIR_BOTH 0
# define LEMIN_DIR_REVERSE -1

/*
** tube_1.c
**
** room1 : first room of the tube
** room2 : second room of the tube
** direction :
** 	1 : natural (room1 -> room2)
** 	0 : both (room1 <-> room2)
** 	-1 : reverse (room1 <- room2)
** cost : constraint from passing through the tube
*/
typedef struct			s_tube
{
	t_room				*room1;
	t_room				*room2;
	int					direction;
	int					cost;
}						t_tube;

typedef struct			s_room_wrapper
{
	t_room				*r1;
	t_room				*r2;
	t_tube				*tube;
}						t_room_wrapper;

int						tube_equals(void *o1, void *o2);

/*
** create a t_tube instance
** return :
** 	t_tube* : created instance
** 	NULL : error
*/
t_tube					*tube_initialize(t_room *room1, t_room *room2,
	int direction, int cost);

/*
** add a tube to its related rooms
** return :
** 	1 : success
**	0 : error
*/
void					tube_add_to_rooms(t_tube *tube);

void					tube_inverse(t_tube *tube);

/*
** tube_2.c
**
** get the room connected to room with tube
** return :
** 	t_room* : connected room
** 	NULL : error
*/
t_room					*tube_get_connection(t_tube *tube, t_room *room);

t_room					*tube_navigate(t_tube *tube, t_room *room);

/*
** room_4.c
*/
t_tube					*room_get_connection(t_room *r1, t_room *r2);

#endif
