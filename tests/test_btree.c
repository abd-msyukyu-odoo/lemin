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

void			display_btree_ext(t_btree *b)
{
	if (!b)
		return ;
	display_btree_ext(b->left);
	printf("%s : %s\n", b->data->key, (char*)(((test_btree*)b->data)->ext));
	display_btree_ext(b->right);
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
		tbt = (test_btree*)malloc(sizeof(test_btree));
		tbt->data = (t_data){&(in[i])};
		tbt->ext = "ext";
		ft_array_add(&a, tbt);
		ft_btree_add(b, (t_data*)tbt);
	}
	return a;
}

void			test_btree_fill_copy()
{
	t_btree		*b;
	t_array		*data;
	t_btree		*copy;

	b = test_construct_btree();
	data = fill_btree(b);
	copy = test_construct_btree();
	ft_btree_fill_copy(b, copy);
	display_array(data);
	display_btree(copy, 0);
	free_data(data);
	ft_array_free(data);
	ft_btree_free(b);
	ft_btree_free(copy);
}

void			test_btree_fill_array()
{
	t_btree		*b;
	t_array		*data;
	t_array		*a;
	
	b = test_construct_btree();
	data = fill_btree(b);
	a = ft_array_construct(2);
	ft_btree_fill_array(b, &a);
	display_array(data);
	display_array(a);
	free_data(data);
	ft_array_free(data);
	ft_array_free(a);
	ft_btree_free(b);
}

void			test_btree_add(void)
{
	t_btree		*b;
	t_array		*data;
	
	b = test_construct_btree();
	data = fill_btree(b);
	display_array(data);
	display_btree(b, 0);
	free_data(data);
	ft_btree_free(b);
	ft_array_free(data);
}

void			test_btree_replace()
{
	t_btree		*b;
	t_array		*data;
	test_btree	*tbt;

	tbt = (test_btree*)malloc(sizeof(test_btree));
	tbt->data = (t_data){&(in[5])};
	tbt->ext = "addon";
	b = test_construct_btree();
	data = fill_btree(b);
	display_btree_ext(b);
	printf("\nreplacing %s :\n\n", tbt->data.key);
	ft_btree_replace(b, (t_data*)tbt);
	display_btree_ext(b);
	free_data(data);
	ft_btree_free(b);
	ft_array_free(data);
	free(tbt);
}

void			test_btree_remove()
{
	t_btree		*b;
	t_array		*data;
	t_array		*a;

	b = test_construct_btree();
	a = ft_array_construct(2);
	data = fill_btree(b);
	display_btree(b, 1);
	printf("\nremoving root:\n	%s\n", &(in[0]));
	ft_btree_remove(b, &(in[0]));
	printf("removing leftnull:\n	%s\n", &(in[3]));
	ft_btree_remove(b, &(in[3]));
	printf("removing rightnull:\n	%s\n", &(in[24]));
	ft_btree_remove(b, &(in[24]));
	printf("removing doublenull:\n	%s\n", &(in[9]));
	ft_btree_remove(b, &(in[9]));
	printf("removing nonull:\n	%s\n\n", &(in[16]));
	ft_btree_remove(b, &(in[16]));
	display_btree(b, 1);
	ft_btree_fill_array(b, &a);
	display_array(a);
	free_data(data);
	ft_btree_free(b);
	ft_array_free(data);
	ft_array_free(a);
}

int				main(void)
{
	//test_btree_add();
	//test_btree_fill_array();
	//test_btree_fill_copy();
	//test_btree_replace();
	test_btree_remove();
	return (0);
}