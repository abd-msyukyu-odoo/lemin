
//TODO add lemin->working_path *s_p_elem
//TODO add lemin->best_path *s_p_elem
//TODO add lemin->paths *s_path
//TODO add lemin->old_paths *t_array<s_path>


//TODO update transfert best path in s_path elem from best path to old paths

/*
**  function update_path
**
**  update the best path with the working path if it is better.
**
**  used by bmf && bfs
**
**
*/

void    update_path(int weight)
{
	if (lemin->end->weight < weight)
		return ;
	lemin->end->weight = weight;
	path_elem_free(&(lemin->best_path));
	path_duplicate(lemin->working_path, &(lemin->best_path));
}

void    algo_add_best_path_to_paths()
{
	path_add_end(&(lemin->paths), lemin->best_path);
	lemin->best_path = NULL;
}

void    algo_add_paths_to_old_paths()
{
	if (ft_array_add(lemin->old_paths, (void *)paths_dup(lemin->paths)) != 1)
		lemin_error(LEMIN_ERR_ARRAY);
}

void    algo_start()
{
	unsigned int    limit;
	unsigned int    nb_paths;

	if (lemin->start->a_tubes->n_items < lemin->end->a_tubes->n_items)
		limit = lemin->start->a_tubes->n_items;
	else
		limit = lemin->end->a_tubes->n_items;
	bfs();
	algo_add_best_path_to_paths();
	algo_add_paths_to_old_paths();
	nb_paths = 1;
	while (nb_paths <= limit)
	{
		// TODO set negative tunnel
		bmf();
		algo_add_best_path_to_paths();
		check_roads(); // TODO check
		cost(); // TODO check
		algo_add_paths_to_old_paths();
		nb_paths++;
	}

}