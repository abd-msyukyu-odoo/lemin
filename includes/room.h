/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:59:04 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 20:59:05 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROOM_H
# define ROOM_H
# include "data.h"
# include "btree.h"
# include "array.h"

typedef struct			s_room
{
	t_data				key;
	t_btree				*bt_tubes;
	t_array				*a_tubes;
	unsigned int		status;
}						t_room;

#endif