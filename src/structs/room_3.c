/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:16:11 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 21:16:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char				*status_str(int status)
{
	static char			*status_str[LEMIN_SIZE_SUFFIX] = {"-I", "-O"};

	return (status_str[status % 2]);
}

char					*lemin_append_status(char *key, int status)
{
	size_t		l;
	char		*out;

	l = (key == NULL) ? 0 : ft_strlen(key);
	out = (char*)ft_memanager_get(g_lemin->mmng, sizeof(char) * (l + 3));
	if (!out)
		lemin_error(LEMIN_ERR_MEM);
	ft_memmove(out, key, l);
	ft_memmove(out + l, status_str(status), 2);
	out[l + 2] = '\0';
	return (out);
}

t_room					*room_get_status(char *key, int status)
{
	t_room				*output;
	t_charkey			ckey;

	ckey.key = (status > -1) ? lemin_append_status(key, status) : key;
	output = ft_hmap_get((t_hmap*)&g_lemin->hm_rooms, &ckey, room_equals);
	ft_memanager_refill(g_lemin->mmng, ckey.key);
	return (output);
}
