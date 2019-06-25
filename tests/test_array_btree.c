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

void			test_array_add(void)
{
	t_array		*a;
	char		*in = "abcdefghijklmnopqrstuvwxyz";

	a = ft_array_construct(0);
	for (int i = 0; i < 26; ++i)
	{
		ft_array_add(&a, &(in[i]));
	}
	display_array(a);
}

int				main(void)
{
	test_array_add();
	return (0);
}
