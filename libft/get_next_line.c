/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 14:26:14 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/25 15:52:31 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

static ssize_t	add_content(const char *src, size_t lsrc, char **line,
		size_t len)
{
	char	*tmp;
	ssize_t	nchar;

	nchar = 0;
	tmp = *line;
	nchar = ft_index_of(src, '\n');
	nchar = (nchar == -1) ? lsrc : nchar;
	*line = (char *)malloc(len + nchar + 1);
	if (*line == NULL)
		return (-1);
	(*line)[len + nchar] = '\0';
	if (tmp != NULL)
		*line = ft_memmove(*line, tmp, len);
	ft_memmove(*line + len, src, nchar);
	ft_strdel(&tmp);
	return (nchar);
}

static ssize_t	reduce_remain(char *remain, char **line)
{
	size_t		len;
	ssize_t		nchar;

	len = ft_strlen(remain);
	if (len > 0)
	{
		if (-1 == (nchar = add_content(remain, len, line, 0)))
			return (-1);
		if ((size_t)nchar != len)
		{
			ft_memmove(remain, remain + nchar + 1, len - nchar);
			if (len - (size_t)nchar == 1)
				remain[0] = '\0';
			return (-2);
		}
		remain[0] = '\0';
		return (nchar);
	}
	return (0);
}

static ssize_t	replace_remain(char *remain, char *buff, ssize_t nread,
		ssize_t nchar)
{
	if (nchar == -1)
		return (-1);
	if (nchar != nread)
	{
		ft_memmove(remain, buff + nchar + 1, nread - nchar - 1);
		remain[nread - nchar - 1] = '\0';
		return (1);
	}
	if (nchar != BUFF_SIZE && nchar > 0)
	{
		remain[0] = '\0';
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char			remains[OPEN_MAX][BUFF_SIZE + 1];
	ssize_t				nchar;
	ssize_t				nread;
	size_t				len;

	if (fd < 0 || !line || read(fd, remains[fd], 0) == -1 || fd >= OPEN_MAX)
		return (-1);
	*line = NULL;
	nchar = reduce_remain(remains[fd], line);
	if (nchar < 0)
		return ((nchar == -1) ? -1 : 1);
	len = (size_t)nchar;
	while ((nread = read(fd, remains[fd], BUFF_SIZE)))
	{
		remains[fd][nread] = '\0';
		nchar = (nread > -1) ? add_content(remains[fd],
				(size_t)nread, line, len) : -1;
		if ((nread = replace_remain(remains[fd], remains[fd], nread, nchar)))
			return ((int)nread);
		len += (size_t)nchar;
	}
	return ((len == 0) ? 0 : 1);
}
