#ifndef LEMIN_BMF_H
# define LEMIN_BMF_H

//TODO Retirer start et end pour utiliser la globale

typedef struct  s_bhandari
{
	t_room      *start;
	t_room      *end;
	t_array     *working_path;
	t_array     *best_path;
	t_array     *old;
	int         old_cost;
	t_array     *new;
	int         new_cost;
}               t_bhandari;

#endif
