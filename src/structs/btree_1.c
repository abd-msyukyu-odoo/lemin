/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   btree.c											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dabeloos <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/06/17 18:26:10 by dabeloos		  #+#	#+#			 */
/*   Updated: 2019/06/17 18:26:12 by dabeloos		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "lemin.h"

/*
** add item to the btree only if its key is not already present
** return :
** 	1 : success
** 	-1 : btree was not modified
** 	0 : error
*/

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

static t_btree		*ft_btree_get_btree(t_btree *btree,
	char *key)
{
	return (ft_btree_get_btree_with_parent(btree, key, NULL));
}

/*
** get t_data item with key
** return :
** 	t_data* : item with key
** 	NULL : btree does not contains key
*/

t_data				*ft_btree_get_data(t_btree *btree, char *key)
{
	t_btree			*target;

	target = ft_btree_get_btree(btree, key);
	return ((target == NULL) ? NULL : target->data);
}

/*
** replace item only if its key is already present
** return :
** 	t_data* : previous item with key
** 	NULL : btree does not contains key
*/

t_data				*ft_btree_replace(t_btree *btree, t_data *item)
{
	t_btree			*target;
	t_data			*out;

	target = ft_btree_get_btree(btree, item->key);
	if (!target)
		return (NULL);
	out = target->data;
	target->data = item;
	return (out);
}

/*
** check if btree contains key
** return :
** 	1 : btree contains key
** 	0 : btree does not contain key
*/

unsigned int		ft_btree_contains(t_btree *btree, char *key)
{
	return (ft_btree_get_btree(btree, key) != NULL);
}
