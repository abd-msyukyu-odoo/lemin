/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:26:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:26:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "libft.h"

t_array				*ft_array_construct(unsigned int size)
{
	t_array			*out;

	out = (t_array*)malloc(sizeof(t_array));
	if (!out)
		return (NULL);
	out->items = malloc(size * sizeof(void*));
	if (!out->items)
	{
		free(out);
		return (NULL);
	}
	out->n_items = 0;
	out->size = size;
	return (out);
}

void				ft_array_free(t_array *array)
{
	if (array == NULL)
		return ;
	free(array->items);
	free(array);
}

static t_array		*ft_array_double_size(t_array *array)
{
	t_array			*out;

	if (2 * array->size <= array->size)
		return (NULL);
	out = ft_array_construct(2 * array->size);
	if (!out)
		return (NULL);
	while (out->n_items < array->n_items)
	{
		out->items[out->n_items] = array->items[out->n_items];
		out->n_items++;
	}
	return (out);
}

int					ft_array_add(t_array **array, void *item)
{
	t_array			*a;

	a = *array;
	if (!item)
		return (0);
	if (a->n_items >= a->size)
	{
		a = ft_array_double_size(a);
		if (!a)
			return (-1);
		ft_array_free(*array);
		*array = a;
	}
	a->items[a->n_items] = item;
	a->n_items++;
	return (1);
}

int					ft_array_insert(t_array **array, unsigned int index,
	void *item)
{
	t_array			*a;

	a = *array;
	if (index > a->n_items)
		return (-1);
	if (!item)
		return (0);
	if (index == a->n_items)
		return ft_array_add(array, item);
	
}