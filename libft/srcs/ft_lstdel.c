/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 17:38:52 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/19 18:20:12 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;

	if (!alst || !*alst || !del)
		return ;
	next = (*alst)->next;
	while (next)
	{
		ft_lstdelone(alst, del);
		*alst = next;
		next = next->next;
	}
	ft_lstdelone(alst, del);
	*alst = NULL;
}
