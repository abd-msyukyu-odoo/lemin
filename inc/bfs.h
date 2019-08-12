/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:12:57 by dabeloos          #+#    #+#             */
/*   Updated: 2019/08/11 13:12:58 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BFS_H
# define BFS_H
# include <stdlib.h>
# include "data.h"
# include "btree.h"
# include "array.h"
# include "libft.h"
# include "global.h"
# include "track.h"

typedef struct			s_bfs
{
	t_global			*gb;
	t_btree				*bt_rooms;
	t_track				*shortest_track;
}						t_bfs;

#endif