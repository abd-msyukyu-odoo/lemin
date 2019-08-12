/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   track.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 14:24:56 by dabeloos          #+#    #+#             */
/*   Updated: 2019/08/11 14:24:58 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACK_H
# define TRACK_H
# include <stdlib.h>
# include "data.h"
# include "array.h"
# include "btree.h"
# include "room.h"
# include "libft.h"

typedef struct				s_track
{
	t_data					key;
	t_room					*room;
	struct s_track			*previous;
}							t_track;

typedef struct				s_track_mng
{
	t_track					*track;
	t_btree					*bt_tracks;
}							t_track_mng;

void						ft_track_mng_free(t_track_mng *track_mng);

t_track						*ft_track_construct(t_room *room,
	t_track *previous);

t_track_mng					*ft_track_mng_construct(t_room *room);

#endif