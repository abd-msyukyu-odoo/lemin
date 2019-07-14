/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:16:51 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/14 17:31:39 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	move_one_ant(t_global *g, t_ant *a)
{
	add_to_buff(g, "L");
	add_to_buff(g, a->key);
	add_to_buff(g, "-");
	add_to_buff(g, a->actual_room->key);
	if (a->next)
		add_to_buff(g, " ");
	a->actual_room->key = a->actual_room->next;
}

void	move_ants(t_global *g, t_ant **a)
{
	t_ant	*actual;
	t_ant	**address;

	address = a;
	actual = *a;
	if (actual)
	{
		while (actual)
		{
			move_one_ant(g, actual);
			if (!actual->next)
				remove_ant(actual, address);
			address = &(actual->next);
			actual = actual->next;
		}
	}
}

void	launch_ants(s)
{
	t_path	*path;
	t_path	**pointer;

	pointer = &(s->paths);
	path = s->paths;
	while (path)
	{
		if (path->nb_ants > 0 && s->nb_ants)
		(
			s->ants = add_ant(s->ants, s->nb_ants, path->elements);
			s->nb_ants -= 1;
			path->nb_ants -= 1;
		)
		if (path->nb_ants == 0)
			path = remove_path(path);
		else
		{
			pointer = &(path->next);
			path = path->next;
		}
	}
}

//TODO Gestion d'erreur
// "ERROR" si pas assez de données mais quoi si malloc error?

void	print(t_global *s) {
	if (!s)
		write(1, "PRINT ERROR\n", 12);
	else
	{
		while (s->nb_ants > 0)
		{
			move_ants(&(s->ants));
			launch_ants(s);
			add_to_buff(g, "\n");
		}
		while (s->ants)
		{
			move_ants(s->ants);
			add_to_buff(g, "\n");
		}
		destroy_global(s);
	}
	exit(0);
}
