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

void				ft_btree_free(t_btree *btree)
{
	if (btree == NULL)
		return ;
	ft_btree_free(btree->left);
	ft_btree_free(btree->right);
	free(btree);
}

static int			ft_btree_add_below(t_btree *btree, t_data *item)
{
	int				cmpr;
	
	cmpr = btree->cmp(item->key, btree->data->key);
	if (cmpr < 0)
	{
		if (btree->left == NULL)
		{
			btree->left = ft_btree_construct(item);
			return (btree->left == NULL) ? -1 : 1;
		}
		return (2);
	}
	else if (cmpr > 0)
	{
		if (btree->right == NULL)
		{
			btree->right = ft_btree_construct(item);
			return (btree->right == NULL) ? -1 : 1;
		}
		return (3);
	}
	else
		return (0);
}

int					ft_btree_add(t_btree *btree, t_data *item)
{
	t_btree			*cur;
	int				status;

	if (btree->data == NULL)
	{
		btree->data = item;
		return (1);
	}
	cur = btree;
	while (1)
	{
		status = ft_btree_add_below(cur, item);
		if (status == 2)
			cur = cur->left;
		else if (status == 3)
			cur = cur->right;
		else
			return (status);
	}
}

t_btree				*ft_btree_get_btree_with_parent(t_btree *btree,
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
	while (cmpr = cur->cmp(key, btree->data->key))
	{
		*parent = cur;
		if (cmpr < 0 && cur->left)
			cur = cur->left;
		else if (cur->right)
			cur = cur->right;
		else
			return (NULL);
	}
	return (cur);
}

t_btree				*ft_btree_get_btree(t_btree *btree,
	char *key)
{
	return ft_btree_get_btree_with_parent(btree, key, NULL);
}

t_data				*ft_btree_get_data(t_btree *btree, char *key)
{
	t_btree			*target;

	target = ft_btree_get_btree(btree, key);
	return ((target == NULL) ? NULL : target->data);
}

unsigned int		ft_btree_contains(t_btree *btree, char *key)
{
	return (ft_btree_get_btree(btree, key) != NULL);
}

int					ft_btree_replace_branch(t_btree *from, t_btree *old_btree,
	t_btree *new_btree)
{
	if (from->right == old_btree)
		from->right = new_btree;
	else if (from->left == old_btree)
		from->left = new_btree;
	else
		return (0);
	free(old_btree);
	return(1);
}

int					ft_btree_remove_branch(t_btree *from, t_btree *target)
{
	return (ft_btree_replace_branch(from, target, NULL));
}

t_btree				*ft_btree_get_min_btree(t_btree *btree, t_btree **parent)
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

t_data				*ft_btree_remove(t_btree *btree, char *key)
{
	t_btree			*parent;
	t_btree			*target;
	t_btree			*tmp;
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
			ft_btree_remove_branch(parent, target);
	}
	else if (target->right == NULL)
	{
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
	else if (target->left == NULL)
	{
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
	else
	{
		parent = target;
		tmp = ft_btree_get_min_btree(target->right, &parent);
		ft_btree_replace_branch(parent, tmp, tmp->right);
		target->data = tmp->data;
		free(tmp);
	}
}