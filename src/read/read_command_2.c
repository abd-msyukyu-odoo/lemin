/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			read_command_extrema_room(t_lrmanager *mng,
	int (*room_create)(char*), int context)
{
	int				status;

	if (context != LEMIN_CONTEXT_ROOMS)
		return (0);
	if (LEMIN_EOL > read_end_line(mng))
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	status = read_room_format(mng, room_create);
	if (status != LEMIN_ROOM_LEGAL)
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	return (1);
}

static int			read_command_start_room(t_lrmanager *mng, int context)
{
	return (read_command_extrema_room(mng, room_create_start, context));
}

static int			read_command_end_room(t_lrmanager *mng, int context)
{
	return (read_command_extrema_room(mng, room_create_end, context));
}

t_command_f			command_function(int command)
{
	static t_command_f	commands[LEMIN_SIZE_COMMANDS] = {
		read_command_start_room,
		read_command_end_room};

	return (commands[command - 1]);
}

char				*command_name(int command)
{
	static char		*commands[LEMIN_SIZE_COMMANDS] = {
		"start",
		"end"};

	return (commands[command - 1]);
}
