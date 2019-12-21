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

typedef struct			s_step
{
	t_charkey			key;
	struct s_step		*next;
	struct s_step		*prev;
	t_room				*room;
	t_tube				*tube;
}						t_step;

typedef struct			s_path
{
	t_step				*first;
	t_step				*last;
	t_step				*cur;
	int					size;
	int					n_ants;
	struct s_path		*next;
	struct s_path		*prev;
}						t_path;

typedef struct			s_paths
{
	t_path				*first;
	t_path				*last;
}						t_paths;

t_path					*path_refill(t_path *path); //path_refill_elems
t_paths					*paths_refill(t_paths *paths); //path_refill_all -> inutile?
void					path_remove_last(t_path *path); //path_elem_refill_pop
void					path_remove_first(t_path *path); //p_elem_remove_first -> ne fait pas ce qui est attendu (devrait retirer un element dont on passe un pointeur)
void					path_extract_step(t_path *path, t_step *step);
void					path_append(t_path *path, t_room *room); //path_elem_add_end
t_path					*path_clone(t_path *path); //path_elem_dup
t_paths					*paths_clone(t_paths *paths); //paths_dup
void					paths_append(t_paths *paths, t_path *path); //path_add_end

#endif
