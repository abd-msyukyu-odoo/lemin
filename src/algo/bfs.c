/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:12:45 by dabeloos          #+#    #+#             */
/*   Updated: 2019/08/11 13:12:47 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "bfs.h"

t_bfs					*ft_bfs_construct(t_global *gb)
{
	t_bfs				*out;

	out = (t_bfs*)malloc(sizeof(t_bfs));
	if (!out)
		return (NULL);
	out->bt_rooms = ft_btree_construct(NULL);
	out->shortest_track = NULL;
	if (!out->bt_rooms)
		return (NULL);
	return (out);
}

t_bfs					*ft_bfs_free(t_bfs *bfs)
{
	ft_btree_free(bfs->bt_rooms);
}

static int				ft_bfs_track_storage(t_track *track,
	t_bfs *bfs, t_array *a)
{
	
}

t_bfs					*ft_bfs_solve(t_global *gb)
{
	t_track				*
}