/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   btree.h											:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dabeloos <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/06/17 18:28:36 by dabeloos		  #+#	#+#			 */
/*   Updated: 2019/06/17 18:28:38 by dabeloos		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include "lemin.h"

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
**	btree_1
**	5 functions
*/

int						ft_btree_add(t_btree *btree, t_data *item);
t_data					*ft_btree_get_data(t_btree *btree, char *key);
t_data					*ft_btree_replace(t_btree *btree, t_data *item);
unsigned int			ft_btree_contains(t_btree *btree, char *key);

/*
**	btree_2
**	5 functions
*/

t_btree					*ft_btree_construct(t_data *data);
void					ft_btree_free(t_btree *btree);
t_data					*ft_btree_remove(t_btree *btree, char *key);
int						ft_btree_fill_copy(t_btree *old_btree,
							t_btree *new_btree);

/*
**	btree_3
**	5 functions
*/

t_btree					*ft_btree_get_btree_with_parent(t_btree *btree,
	char *key, t_btree **parent);
int						ft_btree_replace_branch(t_btree *from,
	t_btree *old_btree, t_btree *new_btree);
t_btree					*ft_btree_get_min_btree(t_btree *btree,
	t_btree **parent);
void					ft_btree_remove_left_sided(t_btree *parent,
	t_btree *target);
void					ft_btree_remove_right_sided(t_btree *parent,
	t_btree *target);

/*
**	btree_4
**	1 function
*/
int						ft_btree_add_below(t_btree *btree, t_data *item);

#endif
