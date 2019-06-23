/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:26:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:26:12 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"
#include "libft.h"

t_btree				*ft_btree_construct(void *data, t_btree *up)
{
	t_btree			*out;

	out = (t_btree*)malloc(sizeof(t_btree));
	if (!out)
		return (NULL);
	out->data = data;
	out->up = up;
	out->left = NULL;
	out->right = NULL;
	out->cmp = ft_strcmp;
	return (out);
}

void				ft_btree_free(t_btree *btree)
{
	if (btree == NULL)
		return ;
	free_btree(btree->left);
	free_btree(btree->right);
	free(btree);
}

void				*ft_btree_add(t_btree *btree, void *item)
{
	t_btree			*cur;
	int				cmpr;

	if (btree->data == NULL)
	{
		btree->data = item;
	}
	cur = btree;
	while (1)
	{
		cmpr = cur->cmp(item->key, 
	}
}
