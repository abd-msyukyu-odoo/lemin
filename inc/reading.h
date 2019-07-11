#ifndef READING_H
# define READING_H

/*
**	start
**	5 functions
*/

t_global	*start_reading(t_global *s);

/*
**	tools
**	5 functions
*/

int		tablen(char **t);
void	tabfree(char ***t);
int		is_integer(char *s);
char	*get_line(void);
int		get_number(void);

/*
**	tools2
**	2 functions
*/

char	**is_room_line(t_global *s, char *line);
char	**is_tunnel_line(char *line);

#endif
