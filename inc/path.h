#ifndef PATH_H
# define PATH_H

typedef struct	s_p_elem
{
	struct s_p_elem	*next;
	t_room			*room;
	t_tube			*tube;
}				t_p_elem;

typedef struct	s_path
{
	t_p_elem			*elements;
	int					nb_ants;
	int					nb_elements;
	struct s_path		*next;
}				t_path;

void			add_path(void *g, int nba, t_p_elem *elems);
t_path			*remove_path(t_path *p);
t_p_elem		*add_p_elem(t_p_elem *e);
// TODO: implement
void			remove_p_elem(t_p_elem **e);

#endif
