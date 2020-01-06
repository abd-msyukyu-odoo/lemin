/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tube.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			read_tube_room(t_lrmanager *mng, char separator)
{
	if (!read_room_legal_start(mng->file[mng->cur]))
		return (LEMIN_TUBE_ILLEGAL_START);
	while (read_room_legal_content(mng->file[1 + mng->cur++]))
		;
	if (mng->file[mng->cur] != separator)
		return (LEMIN_BAD_LINE);
	return (LEMIN_TUBE_ROOM_LEGAL);
}

static int			read_tube_format(t_lrmanager *mng)
{
	t_char_memory	memory;
	t_char_memory	memory2;
	char			*cur;
	int				status;

	if ((status = read_tube_room(mng, '-')) < 1)
		return (status);
	char_memory_replace(&memory, &mng->file[mng->cur++], '\0');
	cur = &mng->file[mng->cur];
	if ((status = read_tube_room(mng, '\n')) < 1)
		return (status);
	char_memory_replace(&memory2, &mng->file[mng->cur], '\0');
	if (!room_create_tube_pair(&mng->file[mng->cur_line], cur))
		return (LEMIN_BAD_LINE);
	char_memory_recover(&memory);
	char_memory_recover(&memory2);
	if (LEMIN_EOL > read_end_line(mng))
		return (LEMIN_BAD_LINE);
	return (LEMIN_TUBE_LEGAL);
}

int					read_tube(t_lrmanager *mng)
{
	int				status;

	status = read_tube_format(mng);
	if (status > LEMIN_TUBE_ILLEGAL_START)
		return (status);
	else
		return (read_command(mng, LEMIN_CONTEXT_TUBES));
}
