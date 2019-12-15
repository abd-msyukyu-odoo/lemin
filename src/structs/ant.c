/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ant.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pierre <pierre@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/07/13 20:53:03 by pierre			#+#	#+#			 */
/*   Updated: 2019/07/15 08:09:35 by pvanderl		 ###   ########.fr	   */
/*																			*/
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

t_ant	*add_ant(t_ant *ant, int nb, t_p_elem *elem)
{
	char	*s;
	t_ant	*a;

	if (!(s = ft_itoa(nb)))
		return (free_ant(ant));
	if (!(a = (t_ant *)malloc(sizeof(t_ant))))
	{
		free(s);
		return (free_ant(ant));
	}
	a->actual_room = elem;
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

void	remove_ant(t_ant **address, t_ant *a)
{
	*address = a->next;
	free(a->key);
	a->next = NULL;
	free(a);
}

/*
**	function free_ant
**
**	free an ant and all the next ants of the chained list
**
**	@input:	a pointer on the ant to free
**	@out:	NULL
*/

t_ant	*free_ant(t_ant *a)
{
	if (a->next)
		a->next = free_ant(a->next);
	if (a->key)
		free(a->key);
	free(a);
	return (NULL);
}
