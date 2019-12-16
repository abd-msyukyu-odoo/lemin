/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 11:37:59 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/30 13:29:49 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

void		print(t_global *s);
void		print_btree(t_btree *t, char *s);
void		add_to_buff(t_global *g, char *s);

void		print_visu(t_global *s);

#endif
