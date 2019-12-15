/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   array.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dabeloos <dabeloos@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/06/17 18:26:10 by dabeloos		  #+#	#+#			 */
/*   Updated: 2019/07/05 14:09:14 by pvanderl		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "array.h"

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
