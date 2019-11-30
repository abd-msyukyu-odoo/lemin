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
		!(lemin->mmng = ft_memanager_construct_default()))
		return (0);
	if (!(ft_marray_initialize(&lemin->a_rooms, lemin->mmng, 100,
			sizeof(t_room))) ||
		!(ft_marray_initialize(&lemin->a_tubes, lemin->mmng, 100,
			sizeof(t_tube))) ||
		!(lemin->buff = (char*)ft_memanager_get(lemin->mmng,
			BF_SIZE * sizeof(char))))
		lemin_error(LEMIN_ERR_MEM);
	lemin->hm_rooms.mmng = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->nb_ants = 0;
	lemin->next_line = 0;
	lemin->buff_pos = 0;
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
