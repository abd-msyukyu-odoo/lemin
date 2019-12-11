#include "lemin.h"

char		*in = "hivadeyfbcgopzwxklmjtunqsr";

t_global	*lemin = NULL;

void			display_tubes(t_array *a)
{
	t_tube		*tube;

	printf("======display tubes \n");
	for (size_t i = 0; i < a->n_items; ++i)
	{
		tube = (t_tube*)ft_array_get(a, i);
		printf("%s - %s\n", tube->room1->key.key, tube->room2->key.key);
	}
}

void			display_rooms(t_array *a)
{
	t_room		*room;

	printf("======display rooms \n");
	for (size_t i = 0; i < a->n_items; ++i)
	{
		room = (t_room*)ft_array_get(a, i);
		printf("%s\n", room->key.key);
	}
}

int				show_room(void *receiver, void *sent)
{
	t_room		*room;

	room = (t_room*)sent;
	if (!receiver)
	{
		printf("%s\n", room->key.key);
		return (1);
	}
	return (0);
}

void			display_hm(t_mhmap *mhmap, int (*f)(void *receiver, void *sent))
{
	printf("======display hashmap rooms \n");
	ft_hmap_bnode_iteration(NULL, (t_hmap*)mhmap, f);
}

int				main(void)
{
	global_construct();
	global_construct_hashmap_rooms(4);
	read_lemin();
	display_tubes((t_array*)&lemin->a_tubes);
	display_rooms((t_array*)&lemin->a_rooms);
	display_hm(&lemin->hm_rooms, show_room);
	global_free();
	return (0);
}
