/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:20:04 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/16 14:22:05 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t		getsize(int n)
{
	size_t	i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char				*ft_itoa(int n)
{
	char			*s;
	size_t			size;
	unsigned int	n_cpy;

	if (n < -2147483648 || n > 2147483647)
		return (NULL);
	size = getsize(n);
	n_cpy = n;
	if (n < 0)
	{
		n_cpy = -n;
		size++;
	}
	if (!(s = ft_strnew(size)))
		return (NULL);
	s[--size] = n_cpy % 10 + '0';
	while (n_cpy /= 10)
		s[--size] = n_cpy % 10 + '0';
	if (n < 0)
		s[0] = '-';
	return (s);
}
