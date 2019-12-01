/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:34:23 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/15 07:57:34 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H
# define BF_SIZE 32
# include "libft.h"
# include "structs/room.h"
# include "structs/tube.h"

typedef struct	s_global
{
	t_memanager	*mmng;
	t_marray	a_rooms;
	t_marray	a_tubes;
	t_mhmap		hm_rooms;
	t_room		*start;
	t_room		*end;
}				t_global;

/*
**  s_global
**  2 functions
*/
int				global_construct(void);
void			global_construct_hashmap_rooms(size_t n_rooms);
void			global_free(void);

#endif