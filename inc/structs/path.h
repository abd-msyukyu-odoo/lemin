
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
	struct s_p_elem		*next;
	t_room				*room;
	t_tube				*tube;
}						t_p_elem;

typedef struct			s_path
{
	t_p_elem			*elems;
	int					n_ants;
	int					n_elems;
	struct s_path		*next;
}						t_path;

t_path					*path_refill_all(t_path *p);
t_p_elem				*path_refill_elems(t_p_elem *e);

void					path_elem_refill_pop(t_p_elem **elem);
void					p_elem_remove_first(t_p_elem **e);
void					path_elem_add_end(t_p_elem **elem, t_room *room);
t_p_elem				*path_elem_dup(t_p_elem *elem);
t_path					*paths_dup(t_path *path);
void					path_add_end(t_path **path, t_p_elem *element);

#endif
