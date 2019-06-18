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

t_array				*construct_array(unsigned int size)
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

void				free_array(t_array *array)
{
	if (array == NULL)
		return;
	
	free(array);
}
