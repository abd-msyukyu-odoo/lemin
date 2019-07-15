/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:16:51 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/15 08:17:29 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_to_buff(t_global *g, char *s)
{
	while (*s)
	{
		g->buff[(g->buff_pos)++] = *s;
		if (g->buff_pos == BF_SIZE)
		{
			write(1, g->buff, g->buff_pos);
			g->buff_pos = 0;
		}
		s++;
	}
}

void	move_one_ant(t_global *g, t_ant *a)
{
	add_to_buff(g, "L");
	add_to_buff(g, a->key);
	add_to_buff(g, "-");
	add_to_buff(g, a->actual_room->key);
	if (a->next)
		add_to_buff(g, " ");
	a->actual_room = a->actual_room->next;
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
				remove_ant(address, actual);
			address = &(actual->next);
			actual = actual->next;
		}
	}
}

void	launch_ants(t_global *s)
{
	t_path	*path;
	t_path	**pointer;

	pointer = &(s->paths);
	path = s->paths;
	while (path)
	{
		if (path->nb_ants > 0 && s->nb_ants)//TODO remove check
		{
			s->ants = add_ant(s->ants, s->nb_ants, path->elements);
			s->nb_ants -= 1;
			path->nb_ants -= 1;
		}
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
		write(2, "PRINT ERROR\n", 12);
	else
	{
		while (s->nb_ants > 0 || s->ants)
		{
			if (s->nb_ants > 0)
				launch_ants(s);
			move_ants(s, &(s->ants));
			add_to_buff(s, "\n");
		}
		destroy_global(s);
	}
	exit(0);
}
