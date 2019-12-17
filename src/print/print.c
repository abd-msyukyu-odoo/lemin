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

void	add_to_buff(char *s)
{
	while (*s)
	{
		lemin->buff[(lemin->buff_pos)++] = *s;
		if (lemin->buff_pos == BF_SIZE)
		{
			write(1, lemin->buff, lemin->buff_pos);
			lemin->buff_pos = 0;
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

void	move_one_ant(t_ant *a)
{
	add_to_buff("L");
	add_to_buff(a->key);
	add_to_buff("-");
	add_to_buff(a->elem->next->room->key.key);
	if (a->elem->next)
		add_to_buff(" ");
	a->elem = a->elem->next;
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

void	move_ants(t_ant **a)
{
	t_ant	*actual;
	t_ant	**address;

	address = a;
	actual = *a;
	if (actual)
	{
		while (actual)
		{
			move_one_ant(actual);
			if (!actual->elem->next)
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

void	launch_ants()
{
	t_path	*path;
	t_path	**pointer;

	pointer = &(lemin->paths);
	path = lemin->paths;
	while (path)
	{
		if (path->nb_ants > 0 && lemin->nb_ants)
		{
			lemin->ants = add_ant(lemin->ants, lemin->nb_ants, path->elements);
			lemin->nb_ants -= 1;
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
**	function print
**
**	print if the global exists and exit
**
**	@input:	/
**	@out:	/
*/

void	print()
{
	while (lemin->nb_ants > 0 || lemin->ants)
	{
		if (lemin->nb_ants > 0)
			launch_ants();
		move_ants(&(lemin->ants));
		add_to_buff("\n");
	}
	lemin->buff_pos += 1;
	write(1, lemin->buff, lemin->buff_pos);
	ft_memanager_free(lemin->mmng);
	exit(0);
}
