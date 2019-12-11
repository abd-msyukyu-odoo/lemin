/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			read_end_line(t_lrmanager *mng)
{
	if (mng->file[mng->cur] == '\0')
		return (LEMIN_EOF);
	if (mng->file[mng->cur] != '\n')
		return (LEMIN_BAD_LINE);
	mng->cur++;
	mng->cur_line = mng->cur;
	return (LEMIN_EOL);
}

static void			lrmanager_construct(void)
{
	if (!(lemin->lrmng = ft_memanager_get(lemin->mmng, sizeof(t_lrmanager))) ||
		!(lemin->lrmng->file = ft_read(0, "\0")))
		lemin_error(LEMIN_ERR_MEM);
	lemin->lrmng->cur = 0;
	lemin->lrmng->cur_line = 0;
}

void				lrmanager_free(t_lrmanager *lrmng)
{
	if (lrmng->file)
		free(lrmng->file);
}

static void			read_n_ants(t_lrmanager *mng)
{
	mng = lemin->lrmng;
	while (ft_isdigit(mng->file[mng->cur]))
		mng->cur++;
	if (mng->cur == mng->cur_line)
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	lemin->n_ants = ft_atoi(mng->file);
	if (LEMIN_EOL > read_end_line(mng))
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
}

static int			read_room_legal_separator(char c)
{
	return (c == ' ');
}


static int			read_tube_legal_separator(char c)
{
	return (c == '-');
}

static int			read_room_legal_content(char c)
{
	return (!(c == '\n' || c == '\0' ||
		read_tube_legal_separator(c) ||
		read_room_legal_separator(c)));
}

static int			read_room_legal_start(char c)
{
	return (!(c == 'L' || c == '#' || !read_room_legal_content(c)));
}

static void			char_memory_recover(t_char_memory *memory)
{
	*(memory->altered) = memory->original_value;
}

static void			char_memory_replace(t_char_memory *memory, char *src,
	char c)
{
	memory->altered = src;
	memory->original_value = *src;
	*src = c;
}

static int			read_coordinate_legal_start(char c)
{
	return (c == '+' || c == '-');
}

static int			read_room_coordinate(t_lrmanager *mng)
{
	size_t			check;

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

static int			read_room_format(t_lrmanager *mng,
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
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	char_memory_replace(&memory, &mng->file[mng->cur++], '\0');
	read_room_coordinates(mng);
	if (!room_create(&mng->file[mng->cur_line]) ||
		LEMIN_EOL > read_end_line(mng))
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	char_memory_recover(&memory);
	return (LEMIN_ROOM_LEGAL);
}

static int			read_command_extrema_room(t_lrmanager *mng,
	int (*room_create)(char*), int critical)
{
	int				status;

	if (!critical)
		return (0);
	if (LEMIN_EOL > read_end_line(mng))
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	status = read_room_format(mng, room_create);
	if (status != LEMIN_ROOM_LEGAL)
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	return (1);
}

static int			read_command_start_room(t_lrmanager *mng, int critical)
{
	return (read_command_extrema_room(mng, room_create_start, critical));
}

static int			read_command_end_room(t_lrmanager *mng, int critical)
{
	return (read_command_extrema_room(mng, room_create_end, critical));
}

static t_command_f	command_function(int command)
{
	static t_command_f	commands[LEMIN_SIZE_COMMANDS] = {
		read_command_start_room,
		read_command_end_room};
	
	return (commands[command - 1]);
}

static char			*command_name(int command)
{
	static char		*commands[LEMIN_SIZE_COMMANDS] = {
		"start",
		"end"};
	
	return (commands[command - 1]);
}

static int			read_command_legal_start(char c)
{
	return (c == '#');
}

static int			read_command_legal_content(char c)
{
	return (!(c == '\0' || c == '\n'));
}

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

	if (!read_command_legal_start(mng->file[mng->cur++]))
		return (LEMIN_COMMAND_ILLEGAL_START);
	if (!read_command_legal_start(mng->file[mng->cur++]))
		return (LEMIN_COMMENT);
	command = 0;
	while (++command <= LEMIN_SIZE_COMMANDS)
		if (read_command_compare(mng, command))
			return (command);
	return (LEMIN_COMMENT);
}

static int			read_comment(t_lrmanager *mng, int critical)
{
	while (read_command_legal_content(mng->file[mng->cur]))
		mng->cur++;
	if (LEMIN_EOL > read_end_line(mng))
	{
		if (critical)
			lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
		return (0);
	}
	return (1);
}

static int			read_command(t_lrmanager *mng, int critical)
{
	int				status;

	status = read_command_format(mng);
	if (status == LEMIN_COMMAND_ILLEGAL_START)
	{
		if (critical)
			lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
		return (0);
	}
	else if (status > LEMIN_COMMENT && status <= LEMIN_SIZE_COMMANDS)
		return ((*command_function(status))(mng, critical));
	else
		return (read_comment(mng, critical));
}

static int			read_room(t_lrmanager *mng)
{
	int				status;

	status = read_room_format(mng, room_create_pair);
	if (status > LEMIN_ROOM_ILLEGAL_START)
		return (status);
	else
		return (read_command(mng, 1));
}

static int			read_tube_room(t_lrmanager *mng)
{
	if (!read_room_legal_start(mng->file[mng->cur]))
		return (LEMIN_TUBE_ILLEGAL_START);
	while (read_room_legal_content(mng->file[1 + mng->cur++]))
		;
	if (!read_tube_legal_separator(mng->file[mng->cur]))
		return (LEMIN_BAD_LINE);
	return (LEMIN_TUBE_ROOM_LEGAL);
}

static int			read_tube_format(t_lrmanager *mng)
{
	t_char_memory	memory;
	t_char_memory	memory2;
	char			*cur;
	int				status;

	if ((status = read_tube_room(mng)) < 1)
		return (status);
	char_memory_replace(&memory, &mng->file[mng->cur++], '\0');
	cur = &mng->file[mng->cur];
	if ((status = read_tube_room(mng)) < 1)
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

static int			read_tube(t_lrmanager *mng)
{
	int				status;

	status = read_tube_format(mng);
	if (status > LEMIN_TUBE_ILLEGAL_START)
		return (status);
	else
		return (read_command(mng, 0));
}

void				read_lemin(void)
{
	lrmanager_construct();
	read_n_ants(lemin->lrmng);
	while (read_room(lemin->lrmng))
		;
	while (read_tube(lemin->lrmng))
		;
}
