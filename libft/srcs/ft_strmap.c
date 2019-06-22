/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:30:33 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/12 10:05:02 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*out;

	if (!s || !f)
		return (NULL);
	out = ft_strnew(ft_strlen(s));
	if (!out)
		return (NULL);
	i = -1;
	while (*(s + ++i))
		*(out + i) = f(*(s + i));
	return (out);
}
