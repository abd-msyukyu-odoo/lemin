/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:22:12 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/19 18:21:12 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_lstitern(t_list *lst, void (*f)(unsigned int, t_list *elem),
					unsigned int i)
{
	if (lst)
	{
		f(i, lst);
		ft_lstitern(lst->next, f, i + 1);
	}
}

void			ft_lstiteri(t_list *lst, void (*f)(unsigned int, t_list *elem))
{
	if (lst && f)
	{
		f(0, lst);
		ft_lstitern(lst->next, f, 1);
	}
}
