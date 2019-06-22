/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 18:54:56 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/23 16:14:58 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		lstfree(void *content, size_t content_size)
{
	(void) content_size;
	ft_memdel((void *)&content);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elem;
	t_list	*nlst;

	elem = NULL;
	if (!f || !(nlst = ft_lstnew(lst->content, lst->content_size)))
		return (NULL);
	while (lst)
	{
		if (!(elem = f(lst)))
		{
			ft_lstdel(&nlst, lstfree);
			return (NULL);
		}
		ft_lstadd(&elem, nlst);
		lst = lst->next;
	}
	return (nlst);
}
