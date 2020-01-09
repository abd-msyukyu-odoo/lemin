/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:37:59 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/30 13:29:49 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include "tests/testing_print.h"

void    printf_cleared_path()
{
	t_path      *path;
	t_step      *step;

	path = g_lemin->paths->first;
	printf("Paths :\n");
	printf("- Cost: %d\n", g_lemin->paths->cost);
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

	if (!g_lemin->working_path || !g_lemin->working_path->first)
	{
		printf("Empty working_path\n");
		return ;
	}
	step = g_lemin->working_path->first;
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

	if (!g_lemin->best_path)
	{
		printf("no best_path\n");
		return ;
	}
	step = g_lemin->best_path->first;
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

	path = g_lemin->paths->first;
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
	while (i < g_lemin->old_paths->array.n_items)
	{
		paths = *(t_paths **)ft_array_get(&(g_lemin->old_paths->array), i);
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
