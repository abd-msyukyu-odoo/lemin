/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 12:49:56 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/10 14:26:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_itoa_rec(long n, size_t i)
{
	char	*str;

	if (n < 10 && n > -10)
	{
		if (!(str = ft_strnew(i + ((n < 0) ? 2 : 1))))
			return (NULL);
		if (n < 0)
			str[i + 1] = '-';
	}
	else
		str = ft_itoa_rec(n / 10, i + 1);
	if (str != NULL)
		str[i] = ((n < 0) ? -1 : 1) * (n % 10) + '0';
	return (str);
}

char			*ft_itoa2(long n)
{
	return (ft_strrev(ft_itoa_rec(n, 0)));
}
