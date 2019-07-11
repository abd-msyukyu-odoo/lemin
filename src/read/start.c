/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:52:09 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/11 11:01:23 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	function add_room
**
**	add a room in the bt_room from a line
**
**	@input:	a pointer on the global structure
**	@input:	a pointer on the table issued from the line
**
**	@out:	1 of the insert is ok | 0 otherwise
*/

static int		add_room(t_global *s, char **l)
{
	int i;

	i = 1;
	if (!l || ft_btree_get_data(s->bt_rooms, l[0]))
		return (0);
	if (s->next_line != 0)
	{
		if ((s->next_line == 1 &&
				!(s->start = ft_room_create_start(ft_strdup(l[0]), s->bt_rooms,
					ft_atoi(l[1]), ft_atoi(l[2])))) ||
				(s->next_line == 2 &&
					!(s->end = ft_room_create_end(ft_strdup(l[0]), s->bt_rooms,
						ft_atoi(l[1]), ft_atoi(l[2])))))
			i = 0;
		s->next_line = 0;
	}
	else if (!ft_room_create_pair(ft_strdup(l[0]), s->bt_rooms,
				ft_atoi(l[1]), ft_atoi(l[2])))
		i = 0;
	tabfree(&l);
	return (i);
}

/*
**	function add_tunnel
**
**	add a tunnel in the bt_room from a line
**
**	@input:	a pointer on the global structure
**	@input:	a pointer on the table issued from the line
**
**	@out:	1 of the insert is ok | 0 otherwise
*/

static int		add_tunnel(t_global *s, char **l)
{
	int	i;
	int j;

	i = 0;
	if (1 == (j = ft_room_create_tube_pair(l[0], l[1], s->bt_rooms)))
		i = 1;
	tabfree(&l);
	return (i);
}

/*
**	function add_line2
**
**	check and call the right function depending on the type of line
**
**	@input:	a pointer on the global structure
**	@input:	a pointer on the line
**	@input:	a pointer on the status int
**
**	@out:	1 of the insert is ok | 0 otherwise
*/

static int		add_line2(t_global *s, char *line, int *status)
{
	char	**r;
	char	**t;

	if (*status == 0)
		r = is_room_line(s, line);
	if (*status == 0 && r)
		return (add_room(s, r));
	t = is_tunnel_line(line);
	if (t)
	{
		if (*status == 0)
		{
			*status = 1;
			tabfree(&r);
		}
		return (add_tunnel(s, t));
	}
	return (0);
}

/*
**	function add_line
**
**	check for the comments and call add_line2
**
**	@input:	a pointer on the global structure
**	@input:	a pointer on the line
**	@input:	a pointer on the status int
**
**	@out:	/
*/

static void		add_line(t_global *s, char *line, int *status)
{
	int	i;

	i = 0;
	if (line[0] == '#')
	{
		if (line[1] == '#')
		{
			if (0 == ft_strcmp("start", line + 2))
				s->next_line = 1;
			else if (0 == ft_strcmp("end", line + 2))
				s->next_line = 2;
		}
		i = 1;
	}
	else if (add_line2(s, line, status))
		i = 1;
	free(line);
	if (i == 0)
		print(destroy_global(s));
}

/*
**	function start_reading
**
**	manage the reading
**
**	@input:	a pointer on the t_global structure
**
**	@out:	a pointer on the t_global structure or NULL if there was an error
*/

t_global		*start_reading(t_global *s)
{
	char	*line;
	int		status;

	s->next_line = 0;
	if (0 > (s->nb_ants = get_number()) ||
			!(s->bt_rooms = ft_btree_construct(NULL)))
		print(destroy_global(s));
	status = 0;
	while ((line = get_line()))
	{
		if (0 == ft_strcmp("EOF", line))
		{
			free(line);
			return (s);
		}
		else
			add_line(s, line, &status);
	}
	return (destroy_global(s));
}
