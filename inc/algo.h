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
void		algo();

void		bmf();

void		bfs();

#endif

// dans print.h
# define LEM_ERR_DISJOINT -3
// TODO add error message no path found between start and end
# define LEM_ERR_ALGO -4
// TODO add error message algo prolem


//TODO add lemin->working_path *t_p_elem
//TODO add lemin->best_path *t_p_elem
//TODO add lemin->paths *t_path
//TODO add lemin->old_paths *t_array<t_path>
