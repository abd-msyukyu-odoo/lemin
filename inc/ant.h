/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 11:34:02 by pierre            #+#    #+#             */
/*   Updated: 2019/07/13 12:06:14 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANT_H
# define ANT_H

typedef struct		s_ant
{
	s_ant		*next;
	t_p_elem	*actual_room;
	char		*key;
}					t_ant;

void		new_ant(t_ant **ants, char *key);


#endif
