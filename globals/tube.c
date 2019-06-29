/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tube.h"
#include "room.h"

t_tube				*ft_tube_construct(t_room *room1, t_room *room2,
		int direction, int cost)
{
	t_tube			*out;

	out = (t_tube*)malloc(sizeof(t_tube));
	if (!out)
		return (NULL);
	out->direction = direction;
	out->cost = cost;
	out->room1 = room1;
	out->room2 = room2;
	if (ft_strcmp(room1->key.key, room2->key.key) < 0)
		out->key = (t_data){ft_strjoin(room1->key.key, room2->key.key)};
	else
		out->key = (t_data){ft_strjoin(room2->key.key, room1->key.key)};
	if (!out->key.key)
	{
		free(out);
		return (NULL);
	}
	return (out);
}

void				ft_tube_free(t_tube *tube)
{
	if (!tube)
		return ;
	free(tube->key.key);
	free(tube);
}
