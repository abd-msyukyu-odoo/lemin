/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:25:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:25:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_ERROR_H
# define LEMIN_ERROR_H
# define LEMIN_ERR_MEM -1
# define LEMIN_ERR_INSUFFICIENT_DATA -2
# define LEMIN_ERR_DISJOINT -3
# define LEMIN_ERR_ALGO -4
# define LEMIN_ERR_PRINT -5
# define LEMIN_SIZE_ERR_MSG 30

void			lemin_error(int error);

#endif
