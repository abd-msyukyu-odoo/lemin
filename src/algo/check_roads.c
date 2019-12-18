/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_roads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_p_elem	*cr_find_other(t_tube *tube)
{
	t_path			*road;
	t_p_elem		*curr;

	road = lemin->paths;
	while (road)
	{
		curr = road->elems;
		while (curr)
		{
			if (curr->tube == tube)
				return (curr);
			curr = curr->next;
		}
		road = road->next;
	}
	return (NULL);
}

static void		cr_exchange(t_p_elem *cur, t_p_elem *other, t_p_elem **pointer)
{
	t_p_elem	*tmp;
	t_tube		*tmp_tube;

	tmp = other->next->next;
	tmp_tube = other->next->tube;
	p_elem_remove_first(&(other->next));
	other->next = cur->next->next;
	other->tube = cur->next->tube;
	p_elem_remove_first(&(cur->next));
	cur->next = tmp;
	cur->tube = tmp_tube;
	*pointer = other;
}

void			check_roads(void)
{
	t_p_elem		*current;
	t_tube			*t;
	t_p_elem		*other;

	current = lemin->best_path;
	while (current->next)
	{
		t = current->tube;
		if (t->cost == -1)
		{
			if ((other = cr_find_other(t)))
				cr_exchange(current, other, &current);
			else
				lemin_error(LEMIN_ERR_ALGO);
			t->cost = 1;
		}
		current = current->next;
	}
}
