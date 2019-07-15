/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 15:30:13 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/08 18:21:09 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		main(void)
{
	t_global	*s;

	if (!(s = (t_global *)malloc(sizeof(t_global))))
		print(NULL);
	if ((s = start_reading(s)))
	{
		printf("right line\n");
	}
	else
	{
		printf("wrong line\n");
	}
	return (0);
}
