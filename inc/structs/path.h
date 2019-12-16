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

t_p_elem		*path_elem_dup(t_p_elem *elem);
void			path_elem_free(t_p_elem **elem);
t_path			*paths_dup(t_path *path);
void			path_add_end(t_path **path, t_p_elem *element);

#endif
