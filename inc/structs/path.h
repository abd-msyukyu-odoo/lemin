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
	int					cost;
}						t_paths;

/*
** path.c
*/
t_path					*path_refill(t_path *path);
void					path_remove_last(t_path *path);
void					path_extract_step(t_path *path, t_step *step);
void					path_append(t_path *path, t_room *room);
t_path					*path_clone(t_path *path);

/*
** paths.c
*/
t_paths					*paths_clone(t_paths *paths);
void					paths_append(t_paths *paths, t_path *path);

#endif
