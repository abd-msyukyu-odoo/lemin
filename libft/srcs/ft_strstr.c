/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:32:13 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/05 00:18:47 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		size;
	int		n;

	if (*needle == '\0')
		return ((char *)haystack);
	n = ft_strlen(needle);
	size = ft_strlen(haystack) - n + 1;
	i = 0;
	while (i < size && haystack[i])
	{
		if (ft_strncmp(haystack + i, needle, (size_t)n) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return ((void *)0);
}
