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
# include "lemin.h"
# define LEMIN_PRINT_BF_SIZE 5000

void		print(void);

void        printf_working_path();
void        printf_best_path();
void        printf_paths();
void        printf_old_paths();
void        printf_cleared_path();

#endif
