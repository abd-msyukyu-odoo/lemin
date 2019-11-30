/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:52:09 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/11 10:47:19 by pvanderl         ###   ########.fr       */
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
