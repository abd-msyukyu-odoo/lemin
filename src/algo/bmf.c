
#include "lemin.h"

//TODO add bmf_value int to t_room;
//TODO add bmf_visited int to t_room;
//TODO add bmf_best_path global;
//TODO room->bmf_value_is_set = 0;

void    bmf_add_path_to_g(t_global *g)
{
	if (g->bhandari->old && g->bhandari->new)
		ft_array_free(g->bhandari->old);
	if (!(g->bhandari->old = ft_array_dup(g->bhandari->new)) ||
		ft_array_add(g->bhandari->new, (void *)g->bhandari->best_path) != 1)
		print(destroy_global(g));
}

void    bmf_add_path(t_bhandari *b)
{
	if (b->best_path)
		ft_array_free(b->best_path);
	b->best_path = ft_array_dup(b->working_path);
}

t_array *bmf_add_possibilities(t_room *current, t_room *previous)
{
	unsigned int    i;
	unsigned int    l;
	t_room          *room;
	t_array         *array;
	t_tube          *tube;

	l = current->a_tubes->n_items - 1;
	if (!(array = ft_array_construct(2)))
		return (NULL);
	while (l >= 0)
	{
		tube = (t_tube *)ft_array_get(current->a_tubes, l);
		room = ft_tube_get_connection(tube, current);
		if (!room->bmf_value_is_set || room->bmf_visited == 0 || room->bmf_value > (current->bmf_value + tube->cost))
		{
			room->bmf_value = current->bmf_value + tube->cost;
			room->bmf_value_is_set = 1;
			if ((ft_array_add(array, (void *)room)) != 1)
			{
				ft_array_free(array);
				return (NULL);
			}
		}
		l--;
	}
}

void    bmf_recursive(t_global *g, t_room *current, t_toom *previous, int weight)
{
	unsigned int    i;
	t_array         *a;
	t_bhandari      *b;

	b = g->bhandari;
	if (ft_array_add(b->working_path, (void *)current) != 1)
		return (print(destroy_global(g)));
	current->bmf_visited = 1;
	current->bmf_value = weight;
    if (current == g->end)
        return (bmf_add_path(g));
    else
	{
    	if (!(a = bmf_add_possibilities(current, previous)))
    		return (print(destroy_global(g)));
    	i = 0;
    	while (i < a->n_items)
    	{
			bmf_recursive(g, ft_tube_get_connection((t_tube *)ft_array_get(a, i), current), current,
					((t_tube *)ft_array_get(a, i)->cost) + current->bmf_value);
    		i += 1;
    	}
	}
}

void    bellmand_ford(t_global *g)
{
	unsigned int    i;
	t_array         *a;
	t_bhandari      *b;

	b = g->bhandari;
	if (!b || !(b->working_path = ft_array_construct(2)) || !(a = bmf_add_possibilities(g->start, NULL)))
		return (print(destroy_global(g)));
	i = 0;
	while (i < a->n_items)
	{
		bmf_recursive(g, ft_tube_get_connection((t_tube *)ft_array_get(a, i), g->start), g->start);
		i += 1;
	}
	bmf_add_path_to_g(g);
}