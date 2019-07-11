/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:16:51 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/05 11:37:37 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	print_btree(t_btree *t, char *s) {
	if (t)
	{
		printf("%s-%s", s, t->data->key);
		print_btree(t->right, s);
		print_btree(t->left, s);
	}
}

void	print_tmp(t_global *s) {
	printf("NB Ants: %d\n", s->nb_ants);
	if (s->start)
	{
		printf("start room name: %s\n", s->start->key.key);
		print_btree(s->start->bt_tubes, s->start->key.key);
	}
	else
		printf("no start room\n");
	if (s->end)
		printf("end room name: %s\n", s->end->key.key);
	else
		printf("no end room\n");
	if (s->bt_rooms)
	{

	}

}

//TODO Gestion d'erreur
// "ERROR" si pas assez de données mais quoi si malloc error?

void	print(t_global *s) {
	if (!s)
		write(1, "PRINT ERROR\n", 12);
	else
	{
		print_tmp(s);
		write(1, "RECU\n", 5);
		destroy_global(s);
	}
	exit(0);
}
