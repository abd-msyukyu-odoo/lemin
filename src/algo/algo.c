
//TODO add lemin->working_path *s_p_elem
//TODO add lemin->best_path *s_p_elem
//TODO add lemin->paths *s_path
//TODO add lemin->old_paths *t_array<s_path>


//TODO update transfert best path in s_path elem from best path to old paths

void    algo_add_best_path_to_paths()
{
	path_add_end(&(lemin->paths), lemin->best_path);
	lemin->best_path = NULL;
}

void    algo_add_paths_to_old_paths()
{
	ft_array_add(lemin->old_paths, (void *)paths_dup())
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
		bmf();
		algo_add_best_path_to_paths();
		check_roads(); // TODO check
		cost(); // TODO check
		algo_add_paths_to_old_paths();
		nb_paths++;
	}

}