/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					read_end_line(t_lrmanager *mng)
{
	if (mng->file[mng->cur] == '\0')
		return (LEMIN_EOF);
	if (mng->file[mng->cur] != '\n')
		return (LEMIN_BAD_LINE);
	mng->cur++;
	mng->cur_line = mng->cur;
	return (LEMIN_EOL);
}

void				char_memory_recover(t_char_memory *memory)
{
	*(memory->altered) = memory->original_value;
}

void				char_memory_replace(t_char_memory *memory, char *src,
	char c)
{
	memory->altered = src;
	memory->original_value = *src;
	*src = c;
}
