/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_lstnew.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pvanderl <pvanderl@students.s19.be>		+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2018/10/04 19:24:31 by pvanderl		  #+#	#+#			 */
/*   Updated: 2018/10/18 15:52:45 by pvanderl		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*elem;

	if (!(elem = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		elem->content = NULL;
		elem->content_size = 0;
	}
	else
	{
		if (!(elem->content = malloc(content_size)))
			return (NULL);
		ft_memcpy(elem->content, content, content_size);
		elem->content_size = content_size;
	}
	elem->next = NULL;
	return (elem);
}
