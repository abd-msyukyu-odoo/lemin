/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_room				*tube_get_connection(t_tube *tube, t_room *room)
{
	if (tube->room1 == room)
		return (tube->room2);
	else if (tube->room2 == room)
		return (tube->room1);
	else
		return (NULL);
}

t_room				*tube_navigate(t_tube *tube, t_room *room)
{
	if (tube->room1 == room && (tube->direction == LEMIN_DIR_NATURAL ||
		tube->direction == LEMIN_DIR_BOTH))
		return (tube->room2);
	if (tube->room2 == room && (tube->direction == LEMIN_DIR_REVERSE ||
		tube->direction == LEMIN_DIR_BOTH))
		return (tube->room1);
	return (NULL);
}
