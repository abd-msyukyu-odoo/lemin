/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:52:09 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/02 08:59:56 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void    add_line(t_global *s, char *line, int *status)
{
    if (ft_strlen(line) > 2)
    if (line[0] == '#')
    {

    }
    else
    {
        if (status == 0)
    }
}

char    *get_line(void)
{
    char    *s;
    int     x;

    x = get_next_line(0, &s);
    if (x == 0)
        return (ft_strdup("EOF"));
    else if (x == 1)
        return (s);
    return (NULL);
}

void    start_reading(t_global *s)
{
    char    *line;
    int     status;

    status = 0;
    while (line = get_line)
    {
        if (0 == ft_strcmp("EOF", line))
            return (check_content(s)); //TODO: check of the recorded content
        else
            add_line(s, line, &status);
    }
    print(destroy_global(s));
}
