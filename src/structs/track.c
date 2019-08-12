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

#include "track.h"

void					ft_track_free(t_track_mng *track_mng)
{

}

int						ft_track_append(t_room *room, t_track_mng *track_mng)
{
	t_track				*out;

	out = (t_track*)malloc(sizeof(t_track));
	if (!out)
		return (NULL);
	out->key = room->key;
	out->room = room;
	out->previous = (!track_mng->track) ? NULL : 
}

t_track_mng				*ft_track_construct(t_room *room)
{
	t_track_mng				*out;

	out = (t_track_mng*)malloc(sizeof(t_track_mng));
	if (!out)
		return (NULL);
	out->bt_tracks = ft_btree_construct(NULL);
	if (!out->bt_tracks)
		return (NULL);
	out->track = NULL;
	out->track = ft_track_append(room, out);
	if (!)
}