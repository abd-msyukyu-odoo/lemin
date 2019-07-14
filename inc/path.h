/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 12:06:31 by pierre            #+#    #+#             */
/*   Updated: 2019/07/13 15:45:18 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

typedef struct	s_p_elem
{
	char		*key;
	s_p_elem	*next;
}				t_p_elem;

typedef struct	s_path
{
	t_p_elem	*elements;
	int			nb_ants;
	s_path		*next;
}				t_path;

void		add_path(t_p_elem *e);
void		remove_path(t_path **p);
p_elem		*add_p_elem(t_p_elem *e);
void		remove_p_elem(t_p_elem **e);

#endif
