/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:56:17 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/15 14:56:20 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H
# define LEMIN_SIZE_COMMANDS 2
# define LEMIN_COMMAND_START 1
# define LEMIN_COMMAND_END 2
# define LEMIN_EOF -1
# define LEMIN_BAD_LINE 0
# define LEMIN_EOL 1
# define LEMIN_ROOM_ILLEGAL_START -1
# define LEMIN_TUBE_LINE 0
# define LEMIN_ROOM_LEGAL 1
# define LEMIN_COMMAND_ILLEGAL_START -1
# define LEMIN_COMMENT 0
# define LEMIN_TUBE_ILLEGAL_START -1
# define LEMIN_TUBE_LEGAL 1
# define LEMIN_TUBE_ROOM_LEGAL 1

typedef struct				s_lrmanager
{
	char					*file;
	size_t					cur;
	size_t					cur_line;
}							t_lrmanager;

typedef struct				s_char_memory
{
	char					*altered;
	char					original_value;
}							t_char_memory;

typedef						int (*t_command_f)(t_lrmanager*, int);

void						lrmanager_free(t_lrmanager *lrmng);

void						read_lemin(void);

#endif
