
static      cr_find_other(t_room *a, t_room *b)
{
	t_array         *roads;
	unsigned int    i;
	t_p_elem        *curr;

	roads = lemin->bhandari; //TODO be sure of the lot
	i = 0;
	while (i < roads->size - 1)
	{
		curr = (t_p_elem *)ft_array_get(roads, i);
		while (curr->next)
		{
			if (curr->room == a && curr->next->room == b)
			{
				t = ft_room_get_tube((t_room *)current->room,
						(t_room *)current->next->room);
				if (t->cost == -1)
					return (curr);
			}
			curr = curr->next;
		}
		i++;
	}
	return (NULL);
}

static      cr_exchange(t_p_elem *cur, t_p_elem *other, t_p_elem **pointer)
{
	s_p_elem    *tmp;

	tmp = other->next->next;
	remove_p_elem(&(other->next));
	other->next = cur->next->next;
	remove_p_elem(&(cur->next));
	cur->next = tmp;
	*pointer = other;
}

void        check_roads(t_array *roads)
{
	unsigned int    i;
	t_p_elem        *current;
	t_tube          *t;
	t_p_elem        *other;

	current = (t_p_elem *)ft_array_get(roads, roads->n_items - 1);
	while (current -> next && current->next->next)
	{
		t = ft_room_get_tube((t_room *)current->room,
		                     (t_room *)current->next->room);
		if (t->cost == -1)
		{
			if ((other = cr_find_other(current->next->room, current->room)))
				cr_exchange(current, other, &current);
			else
				print(destroy_global) // TODO error flow
			t->cost = 1;
		}
		current = current->next;
	}
}
