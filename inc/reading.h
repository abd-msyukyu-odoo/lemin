#ifndef READING_H
# define READING_H

/*
**	start
**	n functions
*/

t_global	*start_reading(t_global *s);

/*
**	r_tools
**	5 functions
*/

int		tablen(char **t);
void	tabfree(char ***t);
int		is_integer(char *s);
char	*get_line(void);
int		get_number(void);


#endif
