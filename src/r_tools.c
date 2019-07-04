/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_tools.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:52:09 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/02 08:59:56 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

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
	while (ft_isdigit(*s))
	{
		i *= 10;
		i += (*s - '0');
		s++;
	}
	i *= sign;
	if (*s == '\0' && i <= 2147483647 && i >= -2147483648)
		return (1);
	return (0);
}
