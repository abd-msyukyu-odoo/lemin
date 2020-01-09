/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legal_char_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:08:31 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/08 18:08:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int					read_room_legal_separator(char c)
{
	return (c == ' ');
}

int					read_tube_legal_separator(char c)
{
	return (c == '-');
}

int					read_room_legal_content(char c)
{
	return (!(c == '\n' || c == '\0' ||
		read_tube_legal_separator(c) ||
		read_room_legal_separator(c)));
}

int					read_room_legal_start(char c)
{
	return (!(c == 'L' || c == '#' || !read_room_legal_content(c)));
}
