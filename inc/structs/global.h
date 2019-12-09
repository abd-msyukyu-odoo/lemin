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
# include "libft.h"
# include "structs/room.h"
# include "structs/tube.h"
# include "structs/ant.h"
# include "structs/path.h"
# include "read/reading.h"

typedef struct	s_global
{
	t_memanager	*mmng;
	t_lrmanager	*lrmng;
	t_marray	a_rooms;
	t_marray	a_tubes;
	t_mhmap		hm_rooms;
	t_room		*start;
	t_room		*end;
	t_ant		*ants;
	int			n_ants;
	t_path		*paths;
}				t_global;

void			global_construct(void);
void			global_construct_hashmap_rooms(size_t n_rooms);
void			global_free(void);

#endif