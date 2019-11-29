/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:53:19 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/15 14:42:27 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			construct_global(void)
{
	if (!(lemin = (t_global*)malloc(sizeof(t_global))) ||
		!(lemin->mmng = ft_memanager_construct_default()) ||
		!(ft_marray_initialize(&lemin->a_rooms, lemin->mmng, 100,
			sizeof(t_room))) ||
		!(ft_marray_initialize(&lemin->a_tubes, lemin->mmng, 100,
			sizeof(t_tube))))
		return (0);
	lemin->hm_rooms.mmng = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	return (1);
}

void		free_global(void)
{
	if (lemin)
	{
		if (lemin->mmng)
			ft_memanager_free(lemin->mmng);
		free(lemin);
	}
}
