/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 11:34:02 by pierre            #+#    #+#             */
/*   Updated: 2019/07/15 08:14:46 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_ALGO_H
# define LEMIN_ALGO_H
# include "structs/path.h"

/*
** cost.c
*/
int			get_cost(void);
void		set_nb_ants(void);

/*
** check_roads_1.c
*/
void		check_roads(void);

/*
** check_roads_2.c
*/
int			cr_find_other(t_path **path);

/*
** bmf.c
*/
void		bmf(void);

/*
** bfs.c
*/
void		bfs(void);

/*
** algo_1.c
*/
void		algo(void);

/*
** algo_2.c
*/
void		set_n_elems(void);
void		set_negatives(void);
void		algo_add_paths_to_old_paths(int cost);
void		algo_add_best_path_to_paths(void);
void		algo_add_tubes_to_best_path(void);

/*
** algo_3.c
*/
void		pop_best_paths(void);
/*
**  function update_path
**
**  update the best path with the working path if it is better.
**
**  used by bmf && bfs
*/
void		update_path(int weight);

#endif
