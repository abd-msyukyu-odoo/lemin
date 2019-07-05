/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:52:09 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/05 17:39:48 by pvanderl         ###   ########.fr       */
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

int		get_number(void)
{
	char	*line;

	while ((line = get_line()) && ft_strlen(line))
	{
		if (is_integer(line))
		{
			free(line);
			return (ft_atoi(line));
		}
		else if (line[0] != '#' || ft_strcmp(line, "##start") ||
				ft_strcmp(line, "##end"))
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	if (line)
		free(line);
	return (-1);
}

/*
**	function get_line
**
**	get a line from the standard input and return "EOF" if there are no more lines
**
**	@in:	/
**
**	@out:	the line or EOF or NULL if error
*/

char		*get_line(void)
{
    char    *s;
    int     x;

    x = get_next_line(0, &s);
    if (x == 0)
        return (ft_strdup("EOF"));
    else if (x == 1)
        return (s);
    return (NULL);
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

int		tablen(char **t)
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

void	tabfree(char ***t) {
	int		i;

	if (*t)
	{
		i = 0;
		while (*t[i])
		{
			free(*t[i]);
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
**	@out:	1 if the argument is an integer | 0 if not
*/

int		is_integer(char *s)
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
