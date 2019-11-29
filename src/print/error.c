/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 10:22:26 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/29 10:22:27 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static char		*error_msg(int error)
{
	static char	**errors = {
		"memory error"};

	return (errors[-1 - error]);
}

void			lemin_error(int error)
{
	free_global();
	ft_printf("%s\n", error_msg(error));
	exit(EXIT_FAILURE);
}
