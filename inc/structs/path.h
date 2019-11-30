
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

typedef struct			s_p_elem
{
	char				*key;
	struct s_p_elem		*next;
}						t_p_elem;

typedef struct			s_path
{
	t_p_elem			*elems;
	int					n_ants;
	struct s_path		*next;
}						t_path;

void					path_add_new(int n_ants, t_p_elem *elems);
t_path					*path_refill_all(t_path *p);
t_p_elem				*p_elem_add(t_p_elem *e, char *key);
t_p_elem				*path_refill_elems(t_p_elem *e);

#endif
