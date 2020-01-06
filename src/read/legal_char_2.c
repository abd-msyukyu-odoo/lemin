/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legal_char_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					read_coordinate_legal_start(char c)
{
	return (c == '+' || c == '-');
}

int					read_command_legal_start(char c)
{
	return (c == '#');
}

int					read_command_legal_content(char c)
{
	return (!(c == '\0' || c == '\n'));
}
