/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 20:58:59 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/28 20:59:00 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUBE_H
# define TUBE_H
# include <stdlib.h>
# include "data.h"
# include "room.h"

typedef struct			s_tube
{
	t_data				key;
	t_room				*room1;
	t_room				*room2;
	int					direction;
	int					cost;
}						t_tube;

/*
** create a t_tube instance
** return :
** 	t_tube* : created instance
** 	NULL : error
*/
t_tube					*ft_tube_construct(t_room *room1, t_room *room2,
							int direction, int cost);

/*
** free the t_tube instance
*/
void					ft_tube_free(t_tube *tube);

#endif