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
	if (!(g_lemin = (t_global*)malloc(sizeof(t_global))))
		lemin_error(LEMIN_ERR_MEM);
	g_lemin->lrmng = NULL;
	g_lemin->rooms_tmng = NULL;
	g_lemin->tubes_tmng = NULL;
	if (!(g_lemin->mmng = ft_memanager_construct(MMNG_DEFAULT_SIZE_COUNT,
		5 * LEMIN_DEFAULT_ROOMS_COUNT,
		500 * LEMIN_DEFAULT_ROOMS_COUNT, 1)) ||
		!(g_lemin->rooms_tmng =
		ft_typemanager_construct(LEMIN_DEFAULT_ROOMS_COUNT, sizeof(t_room))) ||
		!(g_lemin->tubes_tmng =
		ft_typemanager_construct(LEMIN_DEFAULT_TUBES_COUNT, sizeof(t_tube))))
		lemin_error(LEMIN_ERR_MEM);
	ft_typeused_initialize(&g_lemin->rooms_used);
	ft_typeused_initialize(&g_lemin->tubes_used);
	g_lemin->hm_rooms.mmng = NULL;
	g_lemin->start = NULL;
	g_lemin->end = NULL;
	g_lemin->n_ants = 0;
	g_lemin->n_paths = 0;
	g_lemin->buff = ft_marray_construct(g_lemin->mmng, LEMIN_PRINT_BF_SIZE,
		sizeof(char));
	g_lemin->ants = NULL;
}

void		global_construct_hashmap_rooms(size_t n_rooms)
{
	if (!ft_mhmap_initialize(&g_lemin->hm_rooms, g_lemin->mmng, n_rooms,
		ft_hmap_hash_ascii))
		lemin_error(LEMIN_ERR_MEM);
}

void		global_free(void)
{
	if (g_lemin)
	{
		if (g_lemin->tubes_tmng)
			ft_typemanager_free(g_lemin->tubes_tmng);
		if (g_lemin->rooms_tmng)
			ft_typemanager_free(g_lemin->rooms_tmng);
		if (g_lemin->lrmng)
			lrmanager_free(g_lemin->lrmng);
		if (g_lemin->mmng)
			ft_memanager_free(g_lemin->mmng);
		free(g_lemin);
	}
}
