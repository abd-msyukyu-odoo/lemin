#include "lemin.h"
#include "time.h"

char		*in = "hivadeyfbcgopzwxklmjtunqsr";

t_global	*lemin = NULL;

int				show_tube(void *receiver, void *sent)
{
	t_tube		*tube;

	tube = (t_tube*)sent;
	if (!receiver)
	{
		printf("%s - %s\n", tube->room1->key.key, tube->room2->key.key);
		return (1);
	}
	return (0);
}

int				show_tube_ptr(void *receiver, void *sent)
{
	t_tube		**tube;

	tube = (t_tube**)sent;
	return (show_tube(receiver, *tube));
}

void			display_hm(t_mhmap *mhmap, int (*f)(void *receiver, void *sent))
{
	printf("======display hashmap \n");
	ft_hmap_bnode_iteration(NULL, (t_hmap*)mhmap, f);
}

void			display_room(t_room *room)
{
	printf("		name : %s\n", room->key.key);
	printf("___array\n");
	ft_array_iteration(NULL, (t_array*)&room->a_tubes, show_tube_ptr);
}

int				display_room_bnode(void *receiver, void *sent)
{
	t_room		*room;

	room = (t_room*)sent;
	if (receiver)
	{
		display_room(room);
		return (1);
	}
	return (0);
}

int				display_hmap_bnode_iteration(void *receiver, t_hmap *source,
	int (*f)(void *receiver, void *sent))
{
	size_t			i;
	t_btree			*btree;
	int				out;

	i = 0;
	out = 1;
	while (out && i < source->array->size)
	{
		btree = (t_btree*)ft_array_get(source->array, i);
		if (btree->root && btree->root->rank)
		{
			printf("%I64u \n", i);
			out = ft_btree_bnode_iteration(receiver, btree->root, f);
		}
		++i;
	}
	return (out);
}

void			display_hmap_repartition(t_mhmap *m)
{
	display_hmap_bnode_iteration(m, (t_hmap*)m, display_room_bnode);
	printf("n_items : %I64u\nsize : %I64u\n", m->hmap.array->n_items,
		m->hmap.array->size);
}

int				show_room(void *receiver, void *sent)
{
	t_room		*room;

	room = (t_room*)sent;
	if (!receiver)
	{
		display_room(room);
		return (1);
	}
	return (0);
}

void			display_start(t_room *start)
{
	printf("======display start \n");
	display_room(start);
}

void			display_end(t_room *end)
{
	printf("======display end \n");
	display_room(end);
}

void			display_n_ants(int n_ants)
{
	printf("======display n_ants \n");
	printf("%d\n", n_ants);
}

int				main(void)
{
	clock_t		start;
	clock_t		end;

	start = clock();
	global_construct();
	global_construct_hashmap_rooms(LEMIN_DEFAULT_ROOMS_COUNT);
	read_lemin();
	printf("======display lemin's room hashmap\n");
	//display_hmap_repartition(&lemin->hm_rooms);
	display_hm(&lemin->hm_rooms, show_room);
	display_start(lemin->start);
	display_end(lemin->end);
	display_n_ants(lemin->n_ants);
	global_free();
	end = clock();
	printf("%f \n", (double)(end - start) / CLOCKS_PER_SEC);
	return (0);
}
