/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 15:50:26 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/18 15:56:06 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstjoin(t_list *lsta, t_list *lstb)
{
	if (!lstb || !lsta)
		return ;
	while (lsta->next)
		lsta = lsta->next;
	lsta->next = lstb;
}
