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

static t_array		*ft_array_double_size(t_array *array,
	int skip_from)
{
	t_array			*out;
	unsigned int	addon;

	if (2 * array->size <= array->size || skip_from >= array->n_items)
		return (NULL);
	out = ft_array_construct(2 * array->size);
	if (!out)
		return (NULL);
	addon = (skip_from == -1) ? 0 : 1;
	while (out->n_items < array->n_items + addon)
	{
		if (out->n_items == skip_from)
			out->n_items++;
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
		a = ft_array_double_size(a, -1);
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
	unsigned int	i;

	a = *array;
	if (index > a->n_items)
		return (-1);
	if (!item)
		return (0);
	if (index == a->n_items)
		return ft_array_add(array, item);
	i = a->n_items;
	if (a->n_items == a->size)
	{
		a = ft_array_double_size(a, index);
		if (!a)
			return (-1);
		ft_array_free(*array);
		*array = a;
	}
	else
		while (i-- > index)
			a->items[i + 1] = a->items[i];
	a->items[index] = item;
	return (1);
}

void				*ft_array_remove(t_array *array, unsigned int index)
{
	void			*out;
	unsigned int	i;

	if (index >= array->n_items)
		return (NULL);
	out = array->items[index];
	i = index;
	while (++index < array->n_items)
		array->items[index - 1] = array->items[index];
	if (array->n_items > 0)
		array->n_items = array->n_items - 1;
	return (out);
}

unsigned int		ft_array_index(t_array *array, void *item)
{
	unsigned int	i;

	i = 0;
	while (i < array->n_items)
	{
		if (array->items[i] == item)
			return (i);
		i++;
	}
	return (i);
}

int					ft_array_contains(t_array *array, void *item)
{
	return (ft_array_index(array, index) != array->n_items);
}

int					ft_array_remove_first(t_array *array, void *item)
{
	unsigned int	i;

	i = ft_array_index(array, item);
	return (ft_array_remove(array, i));
}
