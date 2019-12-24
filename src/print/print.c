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
		if (lemin->buff_pos == LEMIN_PRINT_BF_SIZE)
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
	add_to_buff(a->step->next->room->key.key);
	if (a->step->next)
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
			if (!actual->step->next)
				ant_remove_refill(address, actual);
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


//TODO laisser la variable pointer, elle permet d'optimiser le tour suivant.
//*************
//check si ce que j'ai fait est coherent avec pointer :
//non, c'est pas cohérent
//*************
void	launch_ants(void)
{
	t_path	*path;
	t_path	**pointer;

	pointer = &(lemin->paths->first);
	path = lemin->paths->first;
	while (path && path->n_ants > 0)
	{
		if (lemin->n_ants)
		{
			lemin->ants = ant_add_new(lemin->ants, lemin->n_ants, path->first);
			lemin->n_ants -= 1;
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

void	print(void)
{
	while (lemin->n_ants > 0 || lemin->ants)
	{
		if (lemin->n_ants > 0)
			launch_ants();
		move_ants(&(lemin->ants));
		add_to_buff("\n");
	}
	lemin->buff_pos += 1;
	write(1, lemin->buff, lemin->buff_pos);
	ft_memanager_free(lemin->mmng);
	exit(0);
}

// TODO remove those debug functions

void    printf_working_path()
{
	t_step  *step;

	if (!lemin->working_path || !lemin->working_path->first)
	{
		printf("Empty working_path\n");
		return ;
	}
	step = lemin->working_path->first;
	printf("Working path: %.1s ", step->room->key.key);
	step = step->next;
	while (step && step->next)
	{
		printf("%.1s ", step->room->key.key);
		step = step->next->next;
	}
	printf("\n");
}

void    printf_best_path()
{
	t_step  *step;

	if (!lemin->best_path)
	{
		printf("no best_path\n");
		return ;
	}
	step = lemin->best_path->first;
	printf("Best path: %.1s ", step->room->key.key);
	step = step->next;
	while (step)
	{
		printf("%.1s ", step->room->key.key);
		step = step->next->next;
	}
	printf("\n");
}

void    printf_paths()
{
	t_path      *path;
	t_step      *step;

	path = lemin->paths->first;
	printf("Paths :\n");
	while (path)
	{
		step = path->first;
		printf("- path: ");
		while (step)
		{
			printf("%.1s ", step->room->key.key);
			if (step->next && step->next->next)
				step = step->next->next;
			else
				step = step->next;
		}
		printf("\n");
		path = path->next;
	}
	printf("\n");
}


//// ATTENTION, ELLE n'est pas bonne (seg fault)
void    printf_old_paths()
{
	unsigned int    i;
	t_path      *path;
	t_step      *step;

	i = 0;
	printf("old paths :\n");
	while (i < lemin->old_paths->array.n_items)
	{
		path = ((t_paths *)ft_array_get(&(lemin->old_paths->array), i))->first;
		printf("- Paths group :\n");
		while (path)
		{
			step = path->first;
			printf("- - path: ");
			while (step)
			{
				printf("%.1s ", step->room->key.key);
				if (step->next && step->next->next)
					step = step->next->next;
				else
					step = step->next;
			}
			printf("\n");
			path = path->next;
		}
		i++;
	}
}
