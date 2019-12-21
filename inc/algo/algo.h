#ifndef LEMIN_ALGO_H
# define LEMIN_ALGO_H
# define FALSE 0
# define TRUE 1

/*
**  function update_path
**
**  update the best path with the working path if it is better.
**
**  used by bmf && bfs
*/

void		update_path(int weight);
void		algo(void);
void		bmf(void);
void		bfs(void);
void		check_roads(void);

int			get_cost(t_paths *paths, int nb_paths);
void        set_nb_ants();

#endif
