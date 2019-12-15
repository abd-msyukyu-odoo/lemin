
static t_room	*cr_find_other(t_tube *tube)
{
	t_path			*road;
	unsigned int	i;
	t_p_elem		*curr;

	road = lemin->paths;
	while (road)
	{
		curr = road->elements;
		while (curr)
		{
			if (curr->tube == tube)
				return (curr);
			curr = curr->next;
		}
		road = road->next;
	}
	return (NULL);
}

static void		cr_exchange(t_p_elem *cur, t_p_elem *other, t_p_elem **pointer)
{
	s_p_elem	*tmp;

	tmp = other->next->next;
	remove_p_elem(&(other->next));
	other->next = cur->next->next;
	remove_p_elem(&(cur->next));
	cur->next = tmp;
	if (!(cur->tube = ft_room_get_tube(cur->room, cur->next->room)) ||
		!(other->tube = ft_room_get_tube(other->room, other->next->room)))
		return (lemin_error(LEM_ERR_MEM));
	*pointer = other;
}

void			check_roads(t_array *roads)
{
	unsigned int	i;
	t_p_elem		*current;
	t_tube			*t;
	t_p_elem		*other;

	current = lemin->best_path;
	while (current->next)
	{
		t = current->tube;
		if (t->cost == -1)
		{
			if ((other = cr_find_other(current->next->room, current->room)))
				cr_exchange(current, other, &current);
			else
				return (lemin_error(LEM_ERR_ALGO));
			t->cost = 1;
		}
		current = current->next;
	}
}
