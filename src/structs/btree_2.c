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

#include "lemin.h"

/*
** create a t_btree instance
** return :
** 	t_btree* : created instance
** 	NULL : error
*/

t_btree				*ft_btree_construct(t_data *data)
{
	t_btree			*out;

	out = (t_btree*)malloc(sizeof(t_btree));
	if (!out)
		return (NULL);
	out->data = data;
	out->left = NULL;
	out->right = NULL;
	out->cmp = ft_strcmp;
	return (out);
}

/*
** free the t_btree instance, but not the items
*/

void				ft_btree_free(t_btree *btree)
{
	if (!btree)
		return ;
	ft_btree_free(btree->left);
	ft_btree_free(btree->right);
	free(btree);
}

static void			ft_btree_remove_min_sided(t_btree *parent, t_btree *target)
{
	t_btree			*tmp;

	parent = target;
	tmp = ft_btree_get_min_btree(target->right, &parent);
	target->data = tmp->data;
	ft_btree_replace_branch(parent, tmp, tmp->right);
}

/*
** remove item with key from the btree
** return :
** 	t_data* : removed item
** 	NULL : btree does not contains key
*/

t_data				*ft_btree_remove(t_btree *btree, char *key)
{
	t_btree			*parent;
	t_btree			*target;
	t_data			*out;

	target = ft_btree_get_btree_with_parent(btree, key, &parent);
	if (target == NULL)
		return (NULL);
	out = target->data;
	if (target->right == NULL && target->left == NULL)
	{
		if (parent == NULL)
			target->data = NULL;
		else
			ft_btree_replace_branch(parent, target, NULL);
	}
	else if (target->right == NULL)
		ft_btree_remove_left_sided(parent, target);
	else if (target->left == NULL)
		ft_btree_remove_right_sided(parent, target);
	else
		ft_btree_remove_min_sided(parent, target);
	return (out);
}

/*
** fill new_btree with all items from old_btree
** return :
** 	1 : success
** 	-1 : btree was not modified
** 	0 : error
*/

int					ft_btree_fill_copy(t_btree *old_btree, t_btree *new_btree)
{
	int				out;

	out = ft_btree_add(new_btree, old_btree->data);
	if (!out && old_btree->left != NULL)
		out = ft_btree_fill_copy(old_btree->left, new_btree);
	if (!out && old_btree->right != NULL)
		out = ft_btree_fill_copy(old_btree->right, new_btree);
	return (out);
}
