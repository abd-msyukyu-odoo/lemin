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

int			global_construct(void)
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

void		global_construct_hashmap_rooms(size_t n_rooms)
{
	if (!ft_mhmap_initialize(&lemin->hm_rooms, lemin->mmng, n_rooms,
		ft_hmap_hash_ascii))
		lemin_error(LEMIN_ERR_MEM);
}

void		global_free(void)
{
	if (lemin)
	{
		if (lemin->mmng)
			ft_memanager_free(lemin->mmng);
		free(lemin);
	}
}


//ADDON

t_global	*generate_global(void)
{
	t_global	*s;

	if (!(s = (t_global *)malloc(sizeof(t_global))))
		print(NULL);
	if (!(s->buff = (char *)malloc(sizeof(char) * BF_SIZE)))
	{
		free(s);
		return (NULL);
	}
	s->start = NULL;
	s->end = NULL;
	s->next_line = 0;
	s->buff_pos = 0;
	return (s);
}