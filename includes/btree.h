/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:28:36 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:28:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H
# include <stdlib.h>
# include "data.h"
# include "array.h"
# include "libft.h"

/*
** data : pointer to a struct that has a t_data as its first member
** left : left child in binary tree
** right : right child in binary tree
** cmp : comparison function used on data->key to sort the binary tree
*/
typedef struct			s_btree
{
	t_data				*data;
	struct s_btree		*left;
	struct s_btree		*right;
	int					(*cmp)(const char *s1, const char *s2);
}						t_btree;

/*
** create a t_btree instance
** return :
** 	t_btree* : created instance
** 	NULL : error
*/
t_btree					*ft_btree_construct(t_data *data);

/*
** free the t_btree instance, but not the items
*/
void					ft_btree_free(t_btree *btree);

/*
** add item to the btree only if its key is not already present
** return :
** 	1 : success
** 	-1 : btree was not modified
** 	0 : error
*/
int						ft_btree_add(t_btree *btree, t_data *item);

/*
** get t_data item with key
** return :
** 	t_data* : item with key
** 	NULL : btree does not contains key
*/
t_data					*ft_btree_get_data(t_btree *btree, char *key);

/*
** replace item only if its key is already present
** return :
** 	t_data* : previous item with key
** 	NULL : btree does not contains key
*/
t_data					*ft_btree_replace(t_btree *btree, t_data *item);

/*
** check if btree contains key
** return :
** 	1 : btree contains key
** 	0 : btree does not contain key
*/
unsigned int			ft_btree_contains(t_btree *btree, char *key);

/*
** remove item with key from the btree
** return :
** 	t_data* : removed item
** 	NULL : btree does not contains key
*/
t_data					*ft_btree_remove(t_btree *btree, char *key);

/*
** fill new_btree with all items from old_btree
** return :
** 	1 : success
** 	-1 : btree was not modified
** 	0 : error
*/
int						ft_btree_fill_copy(t_btree *old_btree,
							t_btree *new_btree);

/*
** fill array with all items from btree
** return :
** 	1 : success
** 	-1 : array was not modified
** 	0 : error
*/
int						ft_btree_fill_array(t_btree *btree, t_array **array);

#endif
