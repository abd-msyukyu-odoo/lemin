/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:30:39 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/12 13:24:39 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*out;
	int		i;

	if (!s || !f)
		return (NULL);
	out = ft_strnew(ft_strlen(s));
	if (!out)
		return (NULL);
	i = -1;
	while (*(s + ++i))
		*(out + i) = f(i, *(s + i));
	return (out);
}
