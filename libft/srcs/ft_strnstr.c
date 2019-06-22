/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:31:43 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/19 14:23:49 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	int		got;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = -1;
	while (++i < len && haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[0])
		{
			k = i;
			got = 1;
			while (haystack[k] && needle[j] && j < len && k < len)
				if (haystack[k++] != needle[j++])
					got = 0;
			if (got && !needle[j])
				return ((char *)(haystack + i));
		}
	}
	return (NULL);
}
