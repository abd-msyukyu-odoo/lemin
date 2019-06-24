/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 13:30:36 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 13:30:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H
# include <stdlib.h>

typedef struct					s_array
{
	void						**items;
	unsigned int				n_items;
	unsigned int				size;
}								t_array;

int					ft_array_add(t_array **array, void *item)

#endif
