/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:30:46 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/20 10:57:10 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	size_t	i;
	size_t	b;

	i = ft_strlen(s1);
	b = 0;
	while (s2[b] && b < n)
	{
		*(s1 + i + b) = *(s2 + b);
		b++;
	}
	*(s1 + b + i) = '\0';
	return (s1);
}
