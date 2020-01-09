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
# include "structs/path.h"
# define LEMIN_DEFAULT_ROOMS_COUNT 5000
# define LEMIN_DEFAULT_TUBES_COUNT 5000

typedef struct		s_global
{
	t_memanager		*mmng;
	t_lrmanager		*lrmng;
	t_typemanager	*rooms_tmng;
	t_typemanager	*tubes_tmng;
	t_typeused		rooms_used;
	t_typeused		tubes_used;
	t_mhmap			hm_rooms;
	t_room			*start;
	t_room			*end;
	t_ant			*ants;
	int				n_ants;
	t_path			*working_path;
	t_path			*best_path;
	t_paths			*paths;
	t_marray		*old_paths;
	t_marray		*buff;
	unsigned int	n_paths;
}					t_global;

void				global_construct(void);
void				global_construct_hashmap_rooms(size_t n_rooms);
void				global_free(void);

#endif
