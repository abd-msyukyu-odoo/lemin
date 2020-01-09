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

# define LEMIN_MAX_READING_SIZE 200000000

# define LEMIN_SIZE_COMMANDS 2
# define LEMIN_COMMAND_START 1
# define LEMIN_COMMAND_END 2

# define LEMIN_COMMAND_ILLEGAL_START -1

# define LEMIN_COMMENT 0

# define LEMIN_EOF -1
# define LEMIN_BAD_LINE 0
# define LEMIN_EOL 1

# define LEMIN_ROOM_ILLEGAL -2
# define LEMIN_ROOM_ILLEGAL_START -1
# define LEMIN_ROOM_LEGAL 1

# define LEMIN_TUBE_LINE 0

# define LEMIN_TUBE_ILLEGAL_START -1
# define LEMIN_TUBE_LEGAL 1
# define LEMIN_TUBE_ROOM_LEGAL 1

# define LEMIN_CONTEXT_ANTS 2
# define LEMIN_CONTEXT_ROOMS 1
# define LEMIN_CONTEXT_TUBES 0

# define LEMIN_ANTS_LEGAL 2

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

typedef int					(*t_command_f)(t_lrmanager*, int);

/*
** legal_char_1.c
*/
int							read_room_legal_separator(char c);
int							read_tube_legal_separator(char c);
int							read_room_legal_content(char c);
int							read_room_legal_start(char c);

/*
** legal_char_2.c
*/
int							read_coordinate_legal_start(char c);
int							read_command_legal_start(char c);
int							read_command_legal_content(char c);

/*
** read_1.c
*/
void						lrmanager_free(t_lrmanager *lrmng);
void						read_lemin(void);

/*
** read_2.c
*/
int							read_end_line(t_lrmanager *mng);
void						char_memory_recover(t_char_memory *memory);
void						char_memory_replace(t_char_memory *memory,
	char *src, char c);

/*
** read_room.c
*/
int							read_room_format(t_lrmanager *mng,
	int (*room_create)(char*));
int							read_room(t_lrmanager *mng);

/*
** read_command_1.c
*/
int							read_command(t_lrmanager *mng, int context);

/*
** read_command_2.c
*/
t_command_f					command_function(int command);
char						*command_name(int command);

/*
** read_tube.c
*/
int							read_tube(t_lrmanager *mng);

/*
** read_ants.c
*/
int							read_ants(t_lrmanager *mng);

#endif
