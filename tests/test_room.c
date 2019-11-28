#include "lemin.h"

//gcc -o test test_room.c ../src/structs/room.c ../src/structs/tube.c ../src/structs/array.c ../src/structs/btree.c -I../includes -I../libft -L../libft/ -lft 

char		*in = "hivadeyfbcgopzwxklmjtunqsr";

void			display_array(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%s \n", ((t_charkey*)ft_array_get(a, i))->key);
	}
	printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

char			*char_btree(t_btree *btree)
{
	if (btree == NULL)
	{
		return ("(null)");
	}
	else
	{
		return (btree->data->key);
	}
}

void			display_btree(t_btree *b, unsigned int verbose)
{
	if (!b)
		return ;
	display_btree(b->left, verbose);
	printf("%s\n", b->data->key);
	if (verbose)
	{
		printf("	left= %s\n	right= %s\n", char_btree(b->left), char_btree(b->right));
	}
	display_btree(b->right, verbose);
}

void			display_tubes(t_btree *bt_rooms)
{
	t_array		*a;
	t_room		*room;

	a = ft_array_construct(0);
	ft_btree_fill_array(bt_rooms, a);
	for (int i = 0; i < a->n_items; ++i)
	{
		room = (t_room*)ft_array_get(a, i);
		printf("%s\n", room->key.key);
		display_array(room->a_tubes);
	}
	ft_array_free(a);
}

void			free_test(t_btree *bt_rooms)
{
	t_array		*a;

	a = ft_array_construct(0);
	ft_btree_fill_array(bt_rooms, a);
	for (int i = 0; i < a->n_items; i++)
		ft_room_free((t_room*)ft_array_get(a, i));
	ft_array_free(a);
	ft_btree_free(bt_rooms);
}

int				main(void)
{
	t_btree		*bt_rooms;

	bt_rooms = ft_btree_construct(NULL);
	ft_room_create_start(ft_strdup(&(in[0])), bt_rooms, 0, 0);
	ft_room_create_end(ft_strdup(&(in[25])), bt_rooms, 0, 0);
	ft_room_create_pair(ft_strdup(&(in[1])), bt_rooms, 0, 0);
	ft_room_create_tube_pair(&(in[0]), &(in[1]), bt_rooms);
	ft_room_create_tube_pair(&(in[0]), &(in[25]), bt_rooms);
	ft_room_create_tube_pair(&(in[25]), &(in[1]), bt_rooms);
	display_tubes(bt_rooms);
	display_btree(bt_rooms, 1);
	free_test(bt_rooms);
	return (0);
}
