/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 17:13:26 by pvanderl          #+#    #+#             */
/*   Updated: 2019/02/23 01:13:00 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	function separate
**
**	separate the content of the t_list. then set the first part to the line,
**	and the second part to the content of t_list
**
**	@param: a pointer on a char chain
**	@param: the t_list element with the current file descritor as content_size
**	@param:	a pointer on the first elem of the list
**	@out:	the int of return of get_next_line
*/

static int				separate(char **line, char **fds, int fd)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (!(ft_strchr(fds[fd], (int)'\n')))
	{
		i = ft_strlen(fds[fd]);
		j = i;
	}
	else
	{
		i = (size_t)(ft_strchr(fds[fd], (int)'\n') - fds[fd]);
		j = i + 1;
	}
	if (!(*line = ft_strnew(i)))
		return (-1);
	*line = ft_strncpy(*line, fds[fd], i);
	if (!(s = ft_strnew(ft_strlen((fds[fd]) + j))))
		return (-1);
	s = ft_strcpy(s, (fds[fd] + j));
	free(fds[fd]);
	fds[fd] = s;
	return (1);
}

/*
**	function get_next_line
**
**	get a line from a file descriptor and assigns a pointer to
**	the designated found line
**
**	@param: file descriptor int
**	@param: pointer to a to a char chain
**
**	@out:	int if succeed (1), end of file (0) or error (-1)
*/

int						get_next_line(const int fd, char **line)
{
	int				retrn;
	char			buf[BUFF_SIZE + 1];
	char			*s;
	static char		*fds[OPEN_MAX];

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	while ((retrn = read(fd, buf, BUFF_SIZE)))
	{
		if (!(buf[retrn] = '\0') && fds[fd])
			s = fds[fd];
		else
			s = ft_strnew(0);
		if (!(fds[fd] = ft_strjoin(s, buf)))
		{
			free(fds[fd]);
			return (-1);
		}
		free(s);
		if (ft_strchr(fds[fd], '\n'))
			break ;
	}
	if (retrn < BUFF_SIZE && (!fds[fd] || !ft_strlen(fds[fd])))
		return (0);
	return (separate(line, fds, fd));
}
