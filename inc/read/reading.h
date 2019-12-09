/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:56:17 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/15 14:56:20 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READING_H
# define READING_H

typedef struct				s_lrmanager
{
	char					*file;
	size_t					cur;
	size_t					cur_line;
}							t_lrmanager;

void						lrmanager_free(t_lrmanager *lrmng);

#endif
