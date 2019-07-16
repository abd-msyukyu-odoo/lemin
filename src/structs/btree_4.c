/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:52:30 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/16 14:52:31 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int			ft_btree_add_below(t_btree *btree, t_data *item)
{
	int				cmpr;

	cmpr = btree->cmp(item->key, btree->data->key);
	if (cmpr < 0)
	{
		if (btree->left == NULL)
		{
			btree->left = ft_btree_construct(item);
			return (btree->left == NULL) ? 0 : 1;
		}
		return (2);
	}
	else if (cmpr > 0)
	{
		if (btree->right == NULL)
		{
			btree->right = ft_btree_construct(item);
			return (btree->right == NULL) ? 0 : 1;
		}
		return (3);
	}
	return (-1);
}
