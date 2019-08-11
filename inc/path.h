/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 14:24:56 by dabeloos          #+#    #+#             */
/*   Updated: 2019/08/11 14:24:58 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H
# include <stdlib.h>
# include "data.h"
# include "array.h"
# include "room.h"
# include "libft.h"

typedef struct				s_path
{
	t_data					key;
	t_room					*room;
	struct s_path			*next;
}							t_path;

#endif