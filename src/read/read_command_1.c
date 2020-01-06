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

static int			read_command_compare(t_lrmanager *mng, int command)
{
	size_t			tmp;

	tmp = mng->cur;
	while (command_name(command)[mng->cur - tmp] &&
		read_command_legal_content(mng->file[mng->cur]) &&
		command_name(command)[mng->cur - tmp] == mng->file[mng->cur])
		mng->cur++;
	return (command_name(command)[mng->cur - tmp] == '\0' &&
		mng->file[mng->cur] == '\n');
}

static int			read_command_format(t_lrmanager *mng)
{
	int				command;

	if (!read_command_legal_start(mng->file[mng->cur]))
		return (LEMIN_COMMAND_ILLEGAL_START);
	mng->cur++;
	if (!read_command_legal_start(mng->file[mng->cur]))
		return (LEMIN_COMMENT);
	mng->cur++;
	command = 0;
	while (++command <= LEMIN_SIZE_COMMANDS)
		if (read_command_compare(mng, command))
			return (command);
	return (LEMIN_COMMENT);
}

static int			read_comment(t_lrmanager *mng, int context)
{
	while (read_command_legal_content(mng->file[mng->cur]))
		mng->cur++;
	if (LEMIN_EOL > read_end_line(mng))
	{
		if (context > LEMIN_CONTEXT_TUBES)
			lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
		return (0);
	}
	return (1);
}

int					read_command(t_lrmanager *mng, int context)
{
	int				status;

	status = read_command_format(mng);
	if (status == LEMIN_COMMAND_ILLEGAL_START)
	{
		if (context > LEMIN_CONTEXT_TUBES)
			lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
		return (0);
	}
	else if (status > LEMIN_COMMENT && status <= LEMIN_SIZE_COMMANDS)
		return ((*command_function(status))(mng, context));
	else
		return (read_comment(mng, context));
}
