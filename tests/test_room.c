#include "array.h"
#include "data.h"
#include "btree.h"
#include "stdio.h"
#include "stdlib.h"
#include "room.h"
#include "tube.h"

//gcc -o test test_room.c ../globals/room.c ../globals/tube.c ../globals/array.c ../globals/btree.c -I../includes -I../libft -L../libft/ -lft 

char		*in = "hivadeyfbcgopzwxklmjtunqsr";

void			display_array(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%s \n", ((t_data*)ft_array_get(a, i))->key);
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

int				main(void)
{
	t_btree		*bt_rooms;
	t_array		*a;

	bt_rooms = ft_btree_construct(NULL);
	a = ft_array_construct(0);
	ft_btree_add(bt_rooms, (t_data*)ft_room_construct(ft_strdup(&(in[0])), 1));
	ft_btree_add(bt_rooms, (t_data*)ft_room_construct(ft_strdup(&(in[25])), 0));
	ft_btree_fill_array(bt_rooms, &a);
	for (int i = 0; i < a->n_items; i++)
	{
		ft_room_free((t_room*)ft_array_get(a, i));
	}
	ft_array_free(a);
	ft_btree_free(bt_rooms);
	return (0);
}