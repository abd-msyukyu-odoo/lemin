/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "room.h"
#include "tube.h"
#include "libft.h"

static t_room			*ft_room_construct(char *key, unsigned int status)
{
	t_room				*out;

	out = (t_room*)malloc(sizeof(t_room));
	if (!out)
		return (NULL);
	out->a_tubes = ft_array_construct(0);
	out->bt_tubes = ft_btree_construct(NULL);
	out->status = status;
	out->key = (t_data){key};
	if (!key || !out->a_tubes || !out->bt_tubes)
	{
		ft_room_free(out);
		return (NULL);
	}
	return (out);
}

int						ft_room_add_tube(t_tube *tube)
{

}

int						ft_room_creator(char *key, t_btree *bt_rooms)
{
	t_room				*in;
	t_room				*out;
	t_tube				*tube;

	in = ft_room_construct(ft_strjoin(key, "#IN"), 0);
	out = ft_room_construct(ft_strjoin(key, "#OUT"), 1);
	free(key);
	if (!in || !out)
		return (-1);
	tube = ft_tube_construct(in, out, 0, 0);
	if (!tube || -1 == ft_room_add_tube(tube, in, out))
	{
		ft_room_free(in);
		ft_room_free(out);
		return (-1);
	}
	return (1);
}

void					ft_room_free(t_room *room)
{
	if (!room)
		return ;
	free(room->a_tubes);
	free(room->bt_tubes);
	free(room->key.key);
	free(room);
}
