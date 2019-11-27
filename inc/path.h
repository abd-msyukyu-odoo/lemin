/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 12:06:31 by pierre            #+#    #+#             */
/*   Updated: 2019/07/15 08:19:29 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

// TODO add double chained list if necessary

typedef struct	s_p_elem
{
	char			*key;
	struct s_p_elem	*next;
	void            *room;
}				t_p_elem;

typedef struct	s_path
{
	t_p_elem			*elements;
	int					nb_ants;
	struct s_path		*next;
}				t_path;

void			add_path(void *g, int nba, t_p_elem *elems);
t_path			*remove_path(t_path *p);
t_p_elem		*add_p_elem(t_p_elem *e);
// TODO: implement
void			remove_p_elem(t_p_elem **e);

#endif
