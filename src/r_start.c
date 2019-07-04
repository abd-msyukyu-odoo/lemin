/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_start.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 16:52:09 by pvanderl          #+#    #+#             */
/*   Updated: 2019/07/03 14:45:44 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	function is_room_line
**
**	check if the line is a given name with x and y coordinates
**
**	@input:	a pointer on the first character of the line
**
**	@out:	the room line table or NULL if not a correct line
*/

char	**is_room_line(char *line)
{
	char	**c;

	c = ft_strsplit(line, ' ');
	if (c)
	{
		if (tablen(c) == 3 && /**/ && is_integer(c[1]) && is_integer(c[2])) //TODO elem !exist
			return (c);
		tabfree(c);
	}
    return (NULL);
}

/*
**	function is_tunnel_line
**
**	check if the line is two existing room_names separated by a '-'
**
**	@input:	a pointer on the first character of the line
**
**	@out:	1 if it is a tunnel line
*/

int		is_tunnel_line(char *line)
{
	char	*s;

	s = ft_strchr(line, '-');
	if (!s || s != ft_strrchr(line, '-'))
		return (-1);
	return (1);
}

int		add_room(t_global *s, char **l)
{
	if ()

	return (1);
}

int		add_tunnel(t_global *s, char *line)
{

	return (1);
}

int		add_line2(t_global *s, char *line, int *status)
{
	char	**r;
	int		t;
//IDEA do only one if status = 1 or both if status  = 0
	r = is_room_line(line);
	t = is_tunnel_line(line);
	if (r && *status == 0)
	{
		add_room(s, r)
		tabfree(r);
		return (1);
	}
	else if (t == 1)
	{
		if (*status == 0)
			*status = 1;
		return (add_tunnel(s, line, status));
	}
	else
	{

		return (0);
	}
	return (1);
}

void    add_line(t_global *s, char *line, int *status)
{
	int	i;

    if (line[0] == '#')
    {
        if (line[1] == '#')
        {
            if (0 == ft_strcmp("start", line + 2))
            {
                //TODO set start room
            }
            else if (0 == ft_strcmp("end", line + 2))
            {
                //TODO set end room
            }
        }
        i = 1;
    }
    else if (add_line2(s, line, status))
    	i = 1;
	free(line);
	if (i == 0)
		print(destroy_global(s))
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
		{
			free(line);
            return (check_content(s)); //TODO: check of the recorded content
		}
		else
            add_line(s, line, &status);
    }
    print(destroy_global(s));
}
