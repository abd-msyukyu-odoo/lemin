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

//TODO a adapter (arbre binaire des rooms empruntees dans chaque path)
static t_step		*cr_find_other(t_tube *tube)
{
	t_path			*road;
	t_step			*cur;

	road = lemin->paths->first;
	while (road)
	{
		cur = road->first;
		while (cur)
		{
			if (cur->tube == tube)
				return (cur);
			cur = cur->next;
		}
		road = road->next;
	}
	return (NULL);
}

//TODO a adapter (echanger plusieurs tubes a la fois si succession de -1 0 -1 0...)
static void			cr_exchange(t_step *cur, t_step *other, t_step **pointer)
{
	t_step			*tmp;
	t_tube			*tmp_tube;

	tmp = other->next->next;
	tmp_tube = other->next->tube;
	//path_remove_first(other->next);// refaire la fonction et la renommer
	other->next = cur->next->next;
	other->tube = cur->next->tube;
	//path_remove_first(cur->next);// refaire la fonction et la renommer
	cur->next = tmp;
	cur->tube = tmp_tube;
	*pointer = other;
}

void				check_roads(void)
{
	t_step			*current;
	t_tube			*t;
	t_step			*other;

	current = lemin->best_path->first;
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
