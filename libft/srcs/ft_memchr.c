/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:25:53 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/12 13:18:38 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*l;

	i = 0;
	l = (const char *)s;
	while (i < n)
	{
		if (l[i] == (char)c)
			return ((void *)l + i);
		i++;
	}
	return ((void *)0);
}
