/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:53:19 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/15 14:42:27 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"

t_global	*generate_global(void)
{
	t_global	*s;

	if (!(s = (t_global *)malloc(sizeof(t_global))))
		print(NULL);
	if (!(s->buff = (char *)malloc(sizeof(char) * BF_SIZE)))
	{
		free(s);
		return (NULL);
	}
	s->start = NULL;
	s->end = NULL;
	s->next_line = 0;
	s->buff_pos = 0;
	return (s);
}

t_global	*destroy_global(t_global *s)
{
	if (s->buff)
		free(s->buff);
	if (s)
		free(s);
	return (NULL);
}
