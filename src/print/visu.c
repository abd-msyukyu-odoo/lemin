/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 13:23:41 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/30 13:41:02 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_visu(t_global *g)
{
	t_path		*path;
	t_p_elem	*elem;
	char		*s;

	path = g->paths;
	while (path)
	{
		s = ft_itoa(path->nb_ants);
		add_to_buff(g, "\n##PATH: ");
		add_to_buff(g, s);
		free(s);
		elem = path->elements;
		while (elem)
		{
			add_to_buff(g, " ");
			add_to_buff(g, elem->key);
			elem = elem->next;
		}
		path = path->next;
	}
}
