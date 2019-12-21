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
**  function update_path
**
**  update the best path with the working path if it is better.
**
**  used by bmf && bfs
*/

void		update_path(int weight);
void		algo(void);
void		bmf(void);
void		bfs(void);
void		check_roads(void);
int			get_cost(t_paths *paths, int nb_paths);
void		set_nb_ants(void);

#endif
