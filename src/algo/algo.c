
//TODO add lemin->working_path *s_p_elem
//TODO add lemin->best_path *s_p_elem
//TODO add lemin->paths *s_path
//TODO add lemin->old_paths *t_array<s_path>

void    algo_push_best_path()
{
	ft_array_add(lemin->old_paths, (void *)path_dup);
}
