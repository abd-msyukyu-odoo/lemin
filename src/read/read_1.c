/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void			lrmanager_construct(void)
{
	if (!(g_lemin->lrmng = ft_memanager_get(g_lemin->mmng,
		sizeof(t_lrmanager))) ||
		!(g_lemin->lrmng->file = ft_read(LEMIN_MAX_READING_SIZE, NULL)))
		lemin_error(LEMIN_ERR_MEM);
	g_lemin->lrmng->cur = 0;
	g_lemin->lrmng->cur_line = 0;
}

void				read_lemin(void)
{
	lrmanager_construct();
	while (read_ants(g_lemin->lrmng) < LEMIN_ANTS_LEGAL)
		;
	while (read_room(g_lemin->lrmng))
		;
	while (read_tube(g_lemin->lrmng))
		;
	if (!g_lemin->start || !g_lemin->end)
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
}

void				lrmanager_free(t_lrmanager *lrmng)
{
	if (lrmng->file)
		free(lrmng->file);
}
