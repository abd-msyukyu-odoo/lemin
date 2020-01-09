/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room			*room_create_extrema(char *key, unsigned int status)
{
	t_room				*extrema;

	extrema = NULL;
	if (status == LEMIN_OUT)
		extrema = room_firewall_initialize(key, LEMIN_OUT);
	else
		extrema = room_firewall_initialize(key, LEMIN_IN);
	return (extrema);
}

int						room_create_start(char *key)
{
	if (g_lemin->start)
		return (0);
	g_lemin->start = room_create_extrema(key, LEMIN_OUT);
	return (g_lemin->start != NULL);
}

int						room_create_end(char *key)
{
	if (g_lemin->end)
		return (0);
	g_lemin->end = room_create_extrema(key, LEMIN_IN);
	return (g_lemin->end != NULL);
}

int						room_create_pair(char *key)
{
	t_room				*in;
	t_room				*out;

	in = room_firewall_initialize(key, LEMIN_IN);
	out = room_firewall_initialize(key, LEMIN_OUT);
	if (!in || !out)
		return (0);
	tube_add_to_rooms(tube_initialize(in, out, LEMIN_DIR_NATURAL, 0));
	return (1);
}
