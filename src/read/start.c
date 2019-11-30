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
**	function get_number
**
**	return the number of ants or -1 if there is an error in the order or
**	in the lines
**
**	@input:	/
**
**	@out:	-1 if error | the number of ants
*/

int			get_number(void)
{
	char	*line;
	int		i;

	i = -2;
	line = NULL;
	while (i == -2 && (line = get_line()) && ft_strlen(line))
	{
		if (is_integer(line))
			i = ft_atoi(line);
		else if (line[0] != '#' || ft_strcmp(line, "##start") ||
				ft_strcmp(line, "##end"))
			i = -1;
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	if (i == -2)
		i = -1;
	return (i);
}

/*
**	function get_line
**
**	get a line from the standard input and
**	return "EOF" if there are no more lines
**
**	@in:	/
**
**	@out:	the line or EOF or NULL if error
*/

char		*get_line(char **start)
{
	char	*s;
	int		x;

	s = ft_strchr(*start, '\n');
	if (s)
	{
	    x = s - start;
        s = ft_strndup(*start, x));
        *start = (*start) + x;
        return (s);
    }
	else
		return (ft_strdup("EOF"));
}

/*
**	function tablen
**
**	return the number of lines in the table
**
**	@input:	a pointer on the first string of the table
**
**	@out:	the length of the table
*/

int			tablen(char **t)
{
	int		i;

	i = 0;
	while (t[i])
		i++;
	return (i);
}

/*
**	function tabfree
**
**	free a table of strings
**
**	@input:	a pointer on the first string of the table
**
**	@out:	/
*/

void		tabfree(char ***t)
{
	int		i;

	if (*t)
	{
		i = 0;
		while ((*t)[i])
		{
			free((*t)[i]);
			i++;
		}
		free(*t);
		*t = NULL;
	}
}

/*
**	function is_integer
**
**	check if the given argument is correct: if it's a correct integer
**
**	@param:	the string to analyze
**
**	@out:	1 if the argument is an integer | 0 if not
*/

int			is_integer(char *s)
{
	long int	i;
	int			sign;

	sign = 1;
	i = 0;
	if (*s == '+')
		s++;
	if (*s == '-')
	{
		s++;
		sign = -1;
	}
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (0);
		i *= 10;
		i += (*s - '0');
		s++;
	}
	i *= sign;
	if (*s == '\0' && i <= 2147483647 && i >= -2147483648)
		return (1);
	return (0);
}

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
    char    *file;
    char    *current;

	s->next_line = 0;
	if (0 > (s->nb_ants = get_number()))
		print(destroy_global(s));
	status = 0;
    file = ft_read(0, '\0');
    current = file;
	while (file && (line = get_line(&current)))
	{
		if (0 == ft_strcmp("EOF", line))
		{
			free(line);
			return (s);
		}
		else
			add_line(s, line, &status);
	}
	if (file)
	    free(file);
	return (destroy_global(s));
}
