/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			read_room_coordinate(t_lrmanager *mng)
{
	size_t			check;
	intmax_t		result;

	check = mng->cur;
	if (read_coordinate_legal_start(mng->file[mng->cur]))
	{
		mng->cur++;
		check = mng->cur;
	}
	while (ft_isdigit(mng->file[mng->cur]))
		mng->cur++;
	if (check == mng->cur)
		return (0);
	result = ft_atoi3(&mng->file[check]);
	if (result > (int)((~((unsigned int)0)) >> 1) ||
		result < (int)(~((~((unsigned int)0)) >> 1)))
		return (0);
	return (1);
}

static void			read_room_coordinates(t_lrmanager *mng)
{
	if (!read_room_coordinate(mng) ||
		!read_room_legal_separator(mng->file[mng->cur++]) ||
		!read_room_coordinate(mng))
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
}

static int			read_is_tube_line(t_lrmanager *mng)
{
	size_t			ahead;

	ahead = mng->cur;
	while (read_room_legal_content(mng->file[ahead]))
		ahead++;
	return (read_tube_legal_separator(mng->file[ahead]));
}

int					read_room_format(t_lrmanager *mng,
	int (*room_create)(char*))
{
	t_char_memory	memory;

	if (!read_room_legal_start(mng->file[mng->cur]))
		return (LEMIN_ROOM_ILLEGAL_START);
	if (read_is_tube_line(mng))
		return (LEMIN_TUBE_LINE);
	while (read_room_legal_content(mng->file[1 + mng->cur++]))
		;
	if (!read_room_legal_separator(mng->file[mng->cur]))
		return (LEMIN_ROOM_ILLEGAL);
	char_memory_replace(&memory, &mng->file[mng->cur++], '\0');
	read_room_coordinates(mng);
	if (!room_create(&mng->file[mng->cur_line]) ||
		LEMIN_EOL > read_end_line(mng))
		return (LEMIN_ROOM_ILLEGAL);
	char_memory_recover(&memory);
	return (LEMIN_ROOM_LEGAL);
}

int					read_room(t_lrmanager *mng)
{
	int				status;

	status = read_room_format(mng, room_create_pair);
	if (status < LEMIN_ROOM_ILLEGAL_START)
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	if (status > LEMIN_ROOM_ILLEGAL_START)
		return (status);
	else
		return (read_command(mng, LEMIN_CONTEXT_ROOMS));
}
