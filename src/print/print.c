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
		if (1 > ft_marray_add(lemin->buff, s++))
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

void	move_one_ant(t_ant *a)
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

void	move_ants(t_ant **a)
{
	t_ant	*actual;
	t_ant	**address;

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

void	launch_ants(void)
{
	t_path	*path;
	t_path	**pointer;

	pointer = &(lemin->paths->first);
	path = lemin->paths->first;
	while (path)
	{
		if (lemin->n_ants && path->n_ants > 0)
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
	write(1, lemin->lrmng->file, lemin->lrmng->cur_line);
	write(1, "\n", 1);
	while (lemin->n_ants > 0 || lemin->ants)
	{
	if (lemin->n_ants > 0)
		launch_ants();
	move_ants(&(lemin->ants));
	add_to_buff("\n");
//		problem to debug :
//	 	if (!lemin->ants && lemin->n_ants > 0)
//		    lemin_error(LEMIN_ERR_PRINT);
	}
//	printf_cleared_path();
	//si jamais on tombe pile sur la taille du buffer on imprime 2x la fin ? non, tkt
	write(1, lemin->buff->array.items, lemin->buff->array.n_items);
	global_free();
	exit(0);
}

// TODO remove those debug functions

void    printf_cleared_path()
{
	t_path      *path;
	t_step      *step;

	path = lemin->paths->first;
	printf("Paths :\n");
	printf("- Cost: %d\n", lemin->paths->cost);
	while (path)
	{
		step = path->first;
		printf("- path: \n- - nAnts: %d\n- - order: ", path->n_ants);
		while (step)
		{
			printf("%.1s ", step->room->key.key);
			step = step->next;
		}
		printf("\n");
		path = path->next;
	}
	printf("\n");
}

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

void    printf_old_paths()
{
	unsigned int    i;
	t_paths         *paths;
	t_path          *path;
	t_step          *step;

	i = 0;
	printf("old paths :\n");
	while (i < lemin->old_paths->array.n_items)
	{
		paths = *(t_paths **)ft_array_get(&(lemin->old_paths->array), i);
		printf("- Paths group :\n");
		printf("- - Cost: %d\n", paths->cost);
		path = paths->first;
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

//void    printf_ants()
//{
//	t_ant   *ant;
//
//	ant = lemin->ants
//}