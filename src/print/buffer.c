/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 15:57:59 by pierre            #+#    #+#             */
/*   Updated: 2019/07/13 16:14:07 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	add_to_buff(t_global *g, char *s)
{
	while (*s)
	{
		g->buff[(g->buff_pos)++] = *s;
		if (s->buff_pos == BUFF_SIZE)
		{
			write(1, s->buff, s->buff_pos);
			s->buff_pos = 0;
		}
		s++;
	}
}
