#include "array.h"
#include "data.h"
#include "btree.h"
#include "stdio.h"

//gcc -o test test_array_btree.c ../globals/array.c ../globals/btree.c -I../includes -I../libft -L../libft/ -lft 

void			display_array(t_array *a)
{
	for (int i = 0; i < a->n_items; ++i)
	{
		printf("%s \n", ft_array_get(a, i));
	}
	printf("n_items : %d\nsize : %d\n", a->n_items, a->size);
}

t_array			*test_construct_array()
{
	t_array		*a;

	a = ft_array_construct(0);
	return (a);
}

void			fill_array(t_array **a)
{
	char		*in = "abcdefghijklmnopqrstuvwxyz";

	for (int i = 0; i < 26; ++i)
	{
		ft_array_add(a, &(in[i]));
	}
}

void			test_array_add(void)
{
	t_array		*a;
	
	
	a = test_construct_array();
	fill_array(&a);
	display_array(a);
	ft_array_free(a);
}

void			test_array_insert(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(&a);
	ft_array_insert(&a, 0, "start");
	ft_array_insert(&a, 5, "inside");
	ft_array_insert(&a, a->n_items, "end");
	display_array(a);
	ft_array_free(a);
}

int				main(void)
{
	//test_array_add();
	test_array_insert();
	return (0);
}
