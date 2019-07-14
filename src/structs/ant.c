/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 20:53:03 by pierre            #+#    #+#             */
/*   Updated: 2019/07/14 17:02:14 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_ant	*add_ant(t_ant *ant, int nb, t_p_elem *elem)
{
	char	*s;
	t_ant	*a;

	if (!(s = ft_itoa(nb)))
		return (free_ant(ant));
	if (!(a = (t_ant *)malloc(sizeof(t_ant))))
	{
		free(s);
		return(free_ant(ant));
	}
	a->next = ant;
	a->key = s;
	return (a);
}

void	remove_ant(t_ant **address, t_ant *a)
{
	*address = a->next;
	free(a->key);
	a->next = NULL;
	free(a);
}

t_ant	*free_ant(t_ant *a)
{
	if (a->next)
		a->next = free_ant(a->next);
	if (a->key)
		free(a->key);
	free(a);
	return (NULL);
}
