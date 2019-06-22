/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:32:26 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/07 19:45:18 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	has_whitespaces(char *str, int *i, size_t *j)
{
	while (ft_isspace(*(str + *i)))
		(*i)++;
	while (ft_isspace(*(str + *j)))
		(*j)--;
	if (*i || *j < ft_strlen(str))
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int			i;
	size_t		j;
	int			k;
	char		*out;
	size_t		new_size;

	if (!s)
		return (NULL);
	i = 0;
	k = 0;
	j = ft_strlen(s) - 1;
	if (!has_whitespaces((char *)s, &i, &j) || !ft_strlen(s))
		return ((char *)s);
	new_size = (i == (int)ft_strlen(s)) ? 0 : ft_strlen(s) - (size_t)i - \
					(ft_strlen(s) - j);
	out = ft_strnew(new_size + 1);
	if (!out)
		return (NULL);
	while (i <= (int)j)
		*(out + k++) = *(s + i++);
	return (out);
}
