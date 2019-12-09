/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void				lrmanager_construct(void)
{
	if (!(lemin->lrmng = ft_memanager_get(lemin->mmng, sizeof(t_lrmanager))) ||
		!(lemin->lrmng->file = ft_read(0, "\0")))
		lemin_error(LEMIN_ERR_MEM);
	lemin->lrmng->cur = 0;
	lemin->lrmng->cur_line = 0;
}

void				lrmanager_free(t_lrmanager *lrmng)
{
	if (lrmng->file)
		free(lrmng->file);
}

static void			goto_next_line(t_lrmanager *mng)
{
	if (mng->file[mng->cur] != '\n')
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	mng->cur++;
	mng->cur_line = mng->cur;
}

static void			read_n_ants(t_lrmanager *mng)
{
	mng = lemin->lrmng;
	while (ft_isdigit(mng->file[mng->cur]))
		mng->cur++;
	if (mng->cur == mng->cur_line)
		lemin_error(LEMIN_ERR_INSUFFICIENT_DATA);
	lemin->n_ants = ft_atoi(mng->file);
	goto_next_line(mng);
}

void				read_lemin(void)
{
	lrmanager_construct();
	read_n_ants(lemin->lrmng);
	//get n_ants
	//get rooms
	//get tubes
	return (1);
}
