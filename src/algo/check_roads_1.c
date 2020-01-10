/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_roads_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				check_roads(void)
{
	t_path			*cur;
	t_tube			*t;

	cur = g_lemin->paths->last;
	cur->cur = cur->first;
	while (cur->cur->next)
	{
		t = cur->cur->tube;
		if (t->cost == LEMIN_DIR_REVERSE)
		{
			if (!cr_find_other(&cur))
				lemin_error(LEMIN_ERR_ALGO);
		}
		tube_inverse(cur->cur->tube);
		cur->cur = cur->cur->next;
	}
}
