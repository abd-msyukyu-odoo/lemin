/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 14:25:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/08/11 14:25:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void					ft_track_free(t_track *track)
{
	t_track				*cur;

	while (track)
	{
		cur = track;
		track = cur->previous;
		free(cur);
	}
}

void					ft_track_mng_free(t_track_mng *track_mng)
{
	ft_btree_free(track_mng->bt_tracks);
	ft_track_free(track_mng->track);
}

t_track					*ft_track_construct(t_room *room, t_track *previous)
{
	t_track				*out;

	out = (t_track*)malloc(sizeof(t_track));
	if (!out)
		return (NULL);
	out->key = room->key;
	out->room = room;
	out->previous = previous;
	return (out);
}

t_track_mng				*ft_track_mng_construct(t_room *room)
{
	t_track_mng				*out;

	out = (t_track_mng*)malloc(sizeof(t_track_mng));
	if (!out)
		return (NULL);
	out->bt_tracks = ft_btree_construct(NULL);
	out->track = ft_track_construct(room, NULL);
	if (!out->track || !out->bt_tracks)
	{
		ft_track_mng_free(out);
		return (NULL);
	}
	return (out);
}