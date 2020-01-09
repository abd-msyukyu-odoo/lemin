/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 20:53:03 by pierre            #+#    #+#             */
/*   Updated: 2019/07/15 08:09:35 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
**	function add_ant
**
**	generate a new ant with a pointer on the starting point of the path and
**	with the right name
**
**	@input:	a pointer on the first ant of the list
**	@input:	the number of the ant wich will become the name of the ant
**	@input:	a pointer on the first element of the path
**	@out:	a pointer on the new generated ant
*/

t_ant			*ant_add_new(t_ant *ant, int n, t_step *step)
{
	char	*s;
	t_ant	*a;

	if (!(s = ft_mitoa(n, g_lemin->mmng)))
		lemin_error(LEMIN_ERR_MEM);
	if (!(a = (t_ant *)ft_memanager_get(g_lemin->mmng, sizeof(t_ant))))
		lemin_error(LEMIN_ERR_MEM);
	a->step = step;
	a->next = ant;
	a->key = s;
	return (a);
}

/*
**	function remove_ant
**
**	remove one ant element of the chained list
**
**	@input:	the address of the pointer from the previous ant in the list
**	@input:	a pointer on the ant to remove
**	@out:	/
*/

void			ant_remove_refill(t_ant **address, t_ant *a)
{
	*address = a->next;
	if (1 > ft_memanager_refill(g_lemin->mmng, a->key))
		lemin_error(LEMIN_ERR_PRINT);
	a->next = NULL;
	if (1 > ft_memanager_refill(g_lemin->mmng, a))
		lemin_error(LEMIN_ERR_PRINT);
}

/*
**	function free_ant
**
**	free an ant and all the next ants of the chained list
**
**	@input:	a pointer on the ant to free
**	@out:	NULL
*/

t_ant			*ant_refill_all(t_ant *a)
{
	if (a->next)
		a->next = ant_refill_all(a->next);
	if (a->key)
		ft_memanager_refill(g_lemin->mmng, a->key);
	ft_memanager_refill(g_lemin->mmng, a);
	return (NULL);
}
