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

#include "lemin.h"

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

void				ft_tube_remove_from_rooms(t_tube *tube)
{
	if (tube->room1)
	{
		ft_array_remove_first(tube->room1->a_tubes, tube);
		ft_btree_remove(tube->room1->bt_tubes, tube->key.key);
	}
	if (tube->room2)
	{
		ft_array_remove_first(tube->room2->a_tubes, tube);
		ft_btree_remove(tube->room2->bt_tubes, tube->key.key);
	}
}

void				ft_tube_free(t_tube *tube)
{
	if (!tube)
		return ;
	ft_tube_remove_from_rooms(tube);
	free(tube->key.key);
	free(tube);
}

int					ft_tube_add_to_rooms(t_tube *tube)
{
	if (!ft_array_add(tube->room1->a_tubes, tube) ||
		!ft_array_add(tube->room2->a_tubes, tube) ||
		!ft_btree_add(tube->room1->bt_tubes, (t_data*)tube) ||
		!ft_btree_add(tube->room2->bt_tubes, (t_data*)tube))
	{
		ft_array_remove_first(tube->room1->a_tubes, tube);
		ft_array_remove_first(tube->room2->a_tubes, tube);
		ft_btree_remove(tube->room1->bt_tubes, tube->key.key);
		return (0);
	}
	return (1);
}

t_room				*ft_tube_get_connection(t_tube *tube, t_room *room)
{
	if (tube->room1 == room)
		return (tube->room2);
	else if (tube->room2 == room)
		return (tube->room1);
	else
		return (NULL);
}
