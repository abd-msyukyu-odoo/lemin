/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:52:09 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/05 17:32:30 by pvanderl         ###   ########.fr       */
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

int		add_room(t_global *s, char **l)
{
	int i;

	i = 1;
	if (!l || !ft_btree_get_data(s->bt_rooms, l[0]))
		return (0);
	if (s->next_line != 0)
	{
		if ((s->next_line == 1 && !(s->start =
			ft_room_create_start(ft_strdup(l[0]), s->bt_rooms))) ||
			(s->next_line == 2 && !(s->end =
			ft_room_create_end(ft_strdup(l[0]), s->bt_rooms))))//TODO ajouter coordonées
			i = 0;
		s->next_line = 0;
	}
	else if (0 == ft_room_create_pair(ft_strdup(l[0]), s->bt_rooms))
		i = 0;
	tabfree(&l);
	return (i);
}

int		add_tunnel(t_global *s, char **l)
{
	int	i;

	i = 0;
	if (ft_btree_get_data(s->bt_rooms, l[0]) &&
		ft_btree_get_data(s->bt_rooms, l[1]) &&
		ft_room_create_tube_pair(l[0], l[1], s->bt_rooms))
		i = 1;
	tabfree(&l);
	return (i);
}

int		add_line2(t_global *s, char *line, int *status)
{
	char	**r;
	char	**t;

	if (*status == 0)
		r = is_room_line(s, line);
	if (*status == 0)
		return(add_room(s, r));
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

void    add_line(t_global *s, char *line, int *status)
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

t_global	*start_reading(t_global *s)
{
    char    *line;
    int     status;

	if (-1 == (s->nb_ants = get_number()) ||
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
