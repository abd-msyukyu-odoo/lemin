#include "array.h"
#include "stdio.h"

//gcc -o test test_array.c ../globals/array.c -I../includes -I../libft -L../libft/ -lft 

char		*in = "abcdefghijklmnopqrstuvwxyz";

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

void			fill_array(t_array *a)
{
	for (int i = 0; i < 26; ++i)
	{
		ft_array_add(a, &(in[i]));
	}
}

void			test_array_add(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(a);
	display_array(a);
	ft_array_free(a);
}

void			test_array_insert(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(a);
	ft_array_insert(a, 0, "start");
	ft_array_insert(a, 5, "inside");
	ft_array_insert(a, a->n_items, "end");
	display_array(a);
	ft_array_free(a);
}

void			test_array_remove(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(a);
	ft_array_remove(a, a->n_items - 1);
	ft_array_remove(a, 3);
	ft_array_remove(a, 0);
	display_array(a);
	ft_array_free(a);
}

void			test_array_index(void)
{
	t_array		*a;

	a = test_construct_array();
	fill_array(a);
	display_array(a);
	printf("first : %d\nfourth : %d\nlast: %d\nfake : %d\n",
		ft_array_index(a, &(in[0])),
		ft_array_index(a, &(in[3])),
		ft_array_index(a, &(in[a->n_items - 1])),
		ft_array_index(a, NULL));
	ft_array_free(a);
}

int				main(void)
{
	test_array_add();
	test_array_insert();
	test_array_remove();
	test_array_index();
	return (0);
}
