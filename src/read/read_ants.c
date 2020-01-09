/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static int			read_ants_format(t_lrmanager *mng)
{
	intmax_t		result;

	mng = g_lemin->lrmng;
	while (ft_isdigit(mng->file[mng->cur]))
		mng->cur++;
	if (mng->cur == mng->cur_line)
		return (LEMIN_BAD_LINE);
	result = ft_atoi3(&mng->file[mng->cur_line]);
	if (result > (int)((~((unsigned int)0)) >> 1) ||
		result == (intmax_t)0 ||
		LEMIN_EOL > read_end_line(mng))
		return (LEMIN_BAD_LINE);
	g_lemin->n_ants = (int)result;
	return (LEMIN_ANTS_LEGAL);
}

int					read_ants(t_lrmanager *mng)
{
	int				status;

	if (mng->file[mng->cur] == '#')
		return (read_command(mng, LEMIN_CONTEXT_ANTS));
	else if (mng->file[mng->cur] == '+')
		mng->cur++;
	status = read_ants_format(mng);
	if (status < LEMIN_ANTS_LEGAL)
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	return (status);
}
