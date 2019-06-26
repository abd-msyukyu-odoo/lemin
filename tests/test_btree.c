#include "array.h"
#include "data.h"
#include "btree.h"
#include "stdio.h"
#include "stdlib.h"

//gcc -o test test_btree.c ../globals/array.c ../globals/btree.c -I../includes -I../libft -L../libft/ -lft 

typedef struct 	s_test_btree
{
	t_data		data;
	void		*ext;
}				test_btree;


char		*in = "hivadeyfbcgopzwxklmjtunqrs";

void			display_array(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%s \n", ((t_data*)ft_array_get(a, i))->key);
	}
	printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

void			display_btree_insert_order(t_btree *b)
{
	t_array		*a;

	a = ft_array_construct(2);
	ft_btree_fill_array(b, &a);
	display_array(a);
	ft_array_free(a);
}

void			display_btree(t_btree *b)
{
	if (!b)
		return ;
	display_btree(b->left);
	printf("%s\n", (b->data->key));
	display_btree(b->right);
}

t_btree			*test_construct_btree()
{
	t_btree		*b;

	b = ft_btree_construct(NULL);
	return (b);
}

void			free_data(t_array *data)
{
	for (int i = 0; i < 26; ++i)
	{
		free(ft_array_get(data, i));
	}
}

t_array			*fill_btree(t_btree *b)
{
	t_array		*a;
	test_btree	*tbt;

	a = ft_array_construct(32);
	for (int i = 0; i < 26; ++i)
	{
		tbt = (test_btree*)malloc(sizeof(tbt));
		tbt->data = (t_data){&(in[i])};
		tbt->ext = "ext";
		ft_array_add(&a, tbt);
		ft_btree_add(b, (t_data*)tbt);
	}
	return a;
}

void			test_btree_add(void)
{
	t_btree		*b;
	t_array		*data;
	
	b = test_construct_btree();
	data = fill_btree(b);
	display_array(data);
	display_btree_insert_order(b);
	display_btree(b);
	free_data(data);
	ft_btree_free(b);
	ft_array_free(data);
}

int				main(void)
{
	test_btree_add();
	return (0);
}