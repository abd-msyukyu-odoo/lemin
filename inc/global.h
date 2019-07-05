/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:34:23 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/05 17:31:39 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

typedef struct	s_global
{
	t_btree		*bt_rooms;
	int			nb_ants;
	t_room		*start;
	t_room		*end;
	int			next_line;
}				t_global;

/*
**  s_global
**  2 functions
*/

t_global    *generate_global();
t_global    *destroy_global(t_global *s);

#endif
