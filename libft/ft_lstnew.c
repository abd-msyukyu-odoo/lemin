/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:23:28 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/17 09:39:33 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new;

	new = (t_list *)ft_memalloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	if (content == NULL || content_size == 0)
	{
		new->content = NULL;
		new->content_size = 0;
		return (new);
	}
	new->content = ft_memalloc(content_size);
	if (new->content == NULL)
	{
		free(new);
		return (NULL);
	}
	new->content = ft_memmove(new->content, content, content_size);
	new->content_size = content_size;
	return (new);
}
