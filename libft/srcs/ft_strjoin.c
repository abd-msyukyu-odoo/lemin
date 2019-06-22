/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:30:10 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/05 20:43:56 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	i;
	size_t	j;
	size_t	s1l;
	size_t	s2l;

	if (!s1 || !s2)
		return (NULL);
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	out = ft_strnew(s1l + s2l);
	if (!out)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < s1l)
		*(out + i) = *(s1 + i);
	while (++j < s2l)
		*(out + i++) = *(s2 + j);
	return (out);
}
