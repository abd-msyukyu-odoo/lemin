#ifndef LEMIN_ALGO_H
# define LEMIN_ALGO_H
# define FALSE 0
# define TRUE 1

typedef struct	s_paths_with_cost
{
	int		cost;
	t_path	*path;
}				t_paths_with_cost;

/*
**  function update_path
**
**  update the best path with the working path if it is better.
**
**  used by bmf && bfs
*/

void		update_path(int weight);
void		algo();
void		bmf();
void		bfs();
void		check_roads();

int			get_cost(t_path *paths, int nb_paths);

#endif
