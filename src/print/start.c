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

/*
**	function add_to_buff
**
**	manage the buffer
**
**	@input:	a pointer on the t_global structure
**	@input:	the string to add to the buffer
**	@out:	/
*/

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

/*
**	function move_one_ant
**
**	move a ant and print each recommended part of the output
**
**	@input: pointer on the t_global structure
**	@input:	a pointer on the ant to print and move
**	@out:	/
*/

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

/*
**	function move_ants
**
**	call move_one_ant for each ant and delete one when needed
**
**	@input:	a pointer on the t_global structure
**	@input:	a pointer on the address of the poiter on the first ant
**	@out:	/
*/

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

/*
**	function launch_ants
**
**	add ants at the beginning of each path with needs ants in it
**
**	@input:	a pointer on the t_global structure
**	@out:	/
*/

/*
**	TODO remove check line 112
*/

void	launch_ants(t_global *s)
{
	t_path	*path;
	t_path	**pointer;

	pointer = &(s->paths);
	path = s->paths;
	while (path)
	{
		if (path->nb_ants > 0 && s->nb_ants)
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

/*
** IDEA Gestion d'erreur print différent si malloc error
*/

/*
**	function print
**
**	print if the global exists and exit
**
**	@input:	a pointer on the t_global structure
**	@out:	/
*/

void	print(t_global *s)
{
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
		s->buff_pos += 1;
		write(1, s->buff, s->buff_pos);
		destroy_global(s);
	}
	exit(0);
}