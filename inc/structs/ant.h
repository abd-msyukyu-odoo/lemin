#ifndef LEMIN_ANT_H
# define LEMIN_ANT_H

# include "structs/path.h"

typedef struct      s_ant
{
	t_p_elem        *elem;
	char            *key;
	struct s_ant    *next;
}                   t_ant;

void                remove_ant(t_ant **address, t_ant *actual);
t_ant               *add_ant(t_ant *a_list, int nb, t_p_elem *elem);

#endif
