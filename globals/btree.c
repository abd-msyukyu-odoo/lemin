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

t_btree				*construct_btree(void* data, t_btree* up)
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