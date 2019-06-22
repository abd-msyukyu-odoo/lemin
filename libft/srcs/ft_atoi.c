/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:19:15 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/20 13:33:53 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	nbr;
	int		a;

	sign = 1;
	nbr = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		a = nbr;
		nbr = nbr * 10 + (int)str[i++] - '0';
		if (a && (a ^ nbr) < 0)
			return ((sign == 1) ? -1 : 0);
	}
	return (sign * nbr);
}
