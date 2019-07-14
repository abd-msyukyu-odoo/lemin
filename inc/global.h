/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 14:34:23 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/14 17:12:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBAL_H
# define GLOBAL_H

# define BUFF_SIZE 32

typedef struct	s_global
{
	t_btree		*bt_rooms;
	int			nb_ants;
	t_room		*start;
	t_room		*end;
	int			next_line;
	t_path		*paths;
	t_ant		*ants;
	char		*buff;
	int			buff_pos;
}				t_global;

/*
**  s_global
**  2 functions
*/

t_global    *generate_global();
t_global    *destroy_global(t_global *s);

#endif
