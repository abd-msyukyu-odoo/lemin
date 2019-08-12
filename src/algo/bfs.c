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

#include "bfs.h"

t_bfs					*ft_bfs_construct(t_global *gb)
{
	t_bfs				*out;

	out = (t_bfs*)malloc(sizeof(t_bfs));
	if (!out)
		return (NULL);
	out->bt_rooms = ft_btree_construct(NULL);
	out->gb = gb;
	out->shortest_track = NULL;
	if (!out->bt_rooms)
	{
		
	}
}