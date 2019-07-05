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

//TODO Gestion d'erreur
// "ERROR" si pas assez de données mais quoi si malloc error?

void	print(t_global *s) {
	if (!s)
		write(1, "ERROR\n", 6);
	else
	{
		write(1, "RECU\n", 5);
		destroy_global(s);
	}
	exit(0);
}
