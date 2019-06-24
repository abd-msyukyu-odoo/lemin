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

typedef struct					s_data
{
	char						*key;
}								t_data;

typedef struct					s_btree
{
	t_data*						data;
	t_btree*					left;
	t_btree*					right;
	int*						(*cmp)(const char *s1, const char *s2);
}								t_btree;

#endif
