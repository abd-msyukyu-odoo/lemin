/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 14:48:00 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/16 14:48:02 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_btree		*ft_btree_get_btree_with_parent(t_btree *btree,
	char *key, t_btree **parent)
{
	t_btree			*cur;
	int				cmpr;

	if (btree->data == NULL)
		return (NULL);
	if (parent == NULL)
		parent = &cur;
	*parent = NULL;
	cur = btree;
	while ((cmpr = cur->cmp(key, cur->data->key)))
	{
		*parent = cur;
		if (cmpr < 0 && cur->left)
			cur = cur->left;
		else if (cmpr > 0 && cur->right)
			cur = cur->right;
		else
			return (NULL);
	}
	return (cur);
}

int			ft_btree_replace_branch(t_btree *from, t_btree *old_btree,
	t_btree *new_btree)
{
	if (from->right == old_btree)
		from->right = new_btree;
	else if (from->left == old_btree)
		from->left = new_btree;
	else
		return (0);
	free(old_btree);
	return (1);
}

t_btree		*ft_btree_get_min_btree(t_btree *btree, t_btree **parent)
{
	t_btree			*cur;

	if (!parent)
		parent = &cur;
	cur = btree;
	while (cur->left)
	{
		*parent = cur;
		cur = cur->left;
	}
	return (cur);
}

void		ft_btree_remove_left_sided(t_btree *parent, t_btree *target)
{
	t_btree			*tmp;

	if (parent == NULL)
	{
		target->data = target->left->data;
		target->right = target->left->right;
		tmp = target->left;
		target->left = target->left->left;
		free(tmp);
	}
	else
		ft_btree_replace_branch(parent, target, target->left);
}

void		ft_btree_remove_right_sided(t_btree *parent,
	t_btree *target)
{
	t_btree			*tmp;

	if (parent == NULL)
	{
		target->data = target->right->data;
		target->left = target->right->left;
		tmp = target->right;
		target->right = target->right->right;
		free(tmp);
	}
	else
		ft_btree_replace_branch(parent, target, target->right);
}
