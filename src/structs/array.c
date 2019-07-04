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

t_array				*ft_array_construct(unsigned int size)
{
	t_array			*out;

	out = (t_array*)malloc(sizeof(t_array));
	if (!out)
		return (NULL);
	if (size > 0)
	{
		out->items = malloc(size * sizeof(void*));
		out->size = size;
	}
	else
	{
		out->items = malloc(sizeof(void*));
		out->size = 1;
	}
	if (!out->items)
	{
		free(out);
		return (NULL);
	}
	out->n_items = 0;
	return (out);
}

void				ft_array_free(t_array *array)
{
	if (!array)
		return ;
	free(array->items);
	free(array);
}

static int			ft_array_double_size(t_array *array, int skip_from)
{
	unsigned int	addon;
	void			**items;
	unsigned int	n_items;

	if (2 * array->size <= array->size || (skip_from > -1 &&
		(unsigned int)skip_from >= array->n_items))
		return (0);
	items = (void**)malloc(2 * array->size * sizeof(void*));
	if (!items)
		return (0);
	addon = (skip_from == -1) ? 0 : 1;
	n_items = 0;
	while (n_items < array->n_items + addon)
	{
		if (n_items == skip_from)
			n_items++;
		items[n_items] = array->items[n_items];
		n_items++;
	}
	free(array->items);
	array->items = items;
	array->n_items = n_items;
	array->size = 2 * array->size;
	return (1);
}

int					ft_array_add(t_array *array, void *item)
{
	if (!item)
		return (-1);
	if (array->n_items >= array->size && !ft_array_double_size(array, -1))
		return (0);
	array->items[array->n_items] = item;
	array->n_items++;
	return (1);
}

int					ft_array_insert(t_array *array, unsigned int index,
	void *item)
{
	unsigned int	i;

	if (index > array->n_items)
		return (0);
	if (!item)
		return (-1);
	if (index == array->n_items)
		return (ft_array_add(array, item));
	i = array->n_items;
	if (array->n_items >= array->size && !ft_array_double_size(array, index))
		return (0);
	else
		while (i-- > index)
			array->items[i + 1] = array->items[i];
	array->items[index] = item;
	array->n_items++;
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
	return (ft_array_index(array, item) != array->n_items);
}

int					ft_array_remove_first(t_array *array, void *item)
{
	unsigned int	i;

	i = ft_array_index(array, item);
	return (ft_array_remove(array, i) != NULL);
}

void				*ft_array_get(t_array *array, unsigned int index)
{
	if (index >= array->n_items)
		return (NULL);
	return (array->items[index]);
}
