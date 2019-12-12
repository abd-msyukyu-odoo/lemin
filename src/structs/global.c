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

void		global_construct(void)
{
	if (!(lemin = (t_global*)malloc(sizeof(t_global))))
		lemin_error(LEMIN_ERR_MEM);
	lemin->lrmng = NULL;
	lemin->rooms_tmng = NULL;
	lemin->tubes_tmng = NULL;
	if (!(lemin->mmng = ft_memanager_construct_default()) ||
		!(lemin->rooms_tmng =
		ft_typemanager_construct(LEMIN_DEFAULT_ROOMS_COUNT, sizeof(t_room))) ||
		!(lemin->tubes_tmng =
		ft_typemanager_construct(LEMIN_DEFAULT_TUBES_COUNT, sizeof(t_tube))))
		lemin_error(LEMIN_ERR_MEM);
	ft_typeused_initialize(&lemin->rooms_used);
	ft_typeused_initialize(&lemin->tubes_used);
	lemin->hm_rooms.mmng = NULL;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->n_ants = 0;
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
		if (lemin->tubes_tmng)
			ft_typemanager_free(lemin->tubes_tmng);
		if (lemin->rooms_tmng)
			ft_typemanager_free(lemin->rooms_tmng);
		if (lemin->lrmng)
			lrmanager_free(lemin->lrmng);
		if (lemin->mmng)
			ft_memanager_free(lemin->mmng);
		free(lemin);
	}
}
