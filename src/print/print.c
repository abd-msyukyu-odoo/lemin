/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:16:51 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/30 13:22:02 by pvanderl         ###   ########.fr       */
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

static void			add_to_buff(char *s)
{
	while (*s)
	{
		if (1 > ft_marray_add(g_lemin->buff, s++))
			lemin_error(LEMIN_ERR_PRINT);
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

static void			move_one_ant(t_ant *a)
{
	add_to_buff("L");
	add_to_buff(a->key);
	add_to_buff("-");
	add_to_buff(a->step->next->room->key.key);
	if (a->next)
		add_to_buff(" ");
	a->step = a->step->next;
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

static void			move_ants(t_ant **a)
{
	t_ant			*actual;
	t_ant			**address;

	address = a;
	actual = *a;
	while (actual)
	{
		move_one_ant(actual);
		if (!actual->step->next)
		{
			ant_remove_refill(address, actual);
			actual = *address;
		}
		else
		{
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

static void			launch_ants(void)
{
	t_path			*path;
	t_path			**pointer;

	pointer = &(g_lemin->paths->first);
	path = g_lemin->paths->first;
	while (path)
	{
		if (g_lemin->n_ants && path->n_ants > 0)
		{
			g_lemin->ants = ant_add_new(g_lemin->ants, g_lemin->n_ants,
				path->first);
			g_lemin->n_ants -= 1;
			path->n_ants -= 1;
			pointer = &(path->next);
		}
		else
			*pointer = path->next;
		path = path->next;
	}
}

/*
**	function print
**
**	print if the global exists and exit
**
**	@input:	/
**	@out:	/
*/

void				print(void)
{
	write(1, g_lemin->lrmng->file, g_lemin->lrmng->cur_line);
	write(1, "\n", 1);
	while (g_lemin->n_ants > 0 || g_lemin->ants)
	{
		if (g_lemin->n_ants > 0)
			launch_ants();
		move_ants(&(g_lemin->ants));
		add_to_buff("\n");
		if (!g_lemin->ants && g_lemin->n_ants > 0)
			lemin_error(LEMIN_ERR_PRINT);
	}
	write(1, g_lemin->buff->array.items, g_lemin->buff->array.n_items);
	global_free();
	exit(0);
}
