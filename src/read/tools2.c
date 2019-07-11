/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:49:37 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/11 10:49:39 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	function is_room_line
**
**	check if the line is a given name with x and y coordinates
**
**	@input:	a pointer on the t_global struct
**	@input:	a pointer on the first character of the line
**
**	@out:	the room line table or NULL if not a correct line
*/

char	**is_room_line(t_global *s, char *line)
{
	char	**c;

	c = ft_strsplit(line, ' ');
	if (c)
	{
		if (tablen(c) == 3 &&
				!ft_btree_get_data(s->bt_rooms, c[0]) &&
				is_integer(c[1]) &&
				is_integer(c[2]))
			return (c);
		tabfree(&c);
	}
	return (NULL);
}

/*
**	function is_tunnel_line
**
**	check if the line is two existing room_names separated by a '-'
**
**	@input:	a pointer on the first character of the line
**
**	@out:	1 if it is a tunnel line
*/

char	**is_tunnel_line(char *line)
{
	char	**s;

	s = NULL;
	if ((s = ft_strsplit(line, '-')))
	{
		if (tablen(s) != 2)
			tabfree(&s);
	}
	return (s);
}
