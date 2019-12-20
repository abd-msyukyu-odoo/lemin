/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 11:34:02 by pierre            #+#    #+#             */
/*   Updated: 2019/07/15 08:14:46 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANT_H
# define ANT_H
# include "structs/path.h"

typedef struct		s_ant
{
	struct s_ant	*next;
	t_step			*step;
	char			*key;
}					t_ant;

t_ant				*ant_add_new(t_ant *ant, int n, t_step *step);
t_ant				*ant_refill_all(t_ant *a);
void				ant_remove_refill(t_ant **address, t_ant *a);

#endif
