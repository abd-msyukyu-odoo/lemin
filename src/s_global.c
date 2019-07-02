/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_global.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:53:19 by pvanderl          #+#    #+#             */
/*   Updated: 2019/06/29 16:50:21 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_global    *generate_global()
{
    t_global    *s;
    if (!(s = (t_global *)malloc(sizeof(t_global))))
        print(NULL);
    return (s);
}

t_global    *delete_global(t_global *s)
{
    if (s)
        free(s);
    return (NULL);
}
