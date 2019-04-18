/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 10:59:37 by dabeloos          #+#    #+#             */
/*   Updated: 2019/04/17 10:59:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "yreader.h"

static unsigned char	yread_input(t_string *out, ssize_t *len, size_t sread)
{
	static char		buff[YMAX_RDSZ + 1];
	ssize_t			nread;

	if (sread >= YMAX_RDSZ)
		sread = YMAX_RDSZ;
	if ((nread = read(YINPUT, buff, sread)))
	{
		if (nread < 0 || -1 == (*len = ystr_join(out, *len, buff, nread)))
		{
			free(out->s);
			return (0);
		}
	}
	return (1);
}

static char				*yread_until(char end, char *rmn)
{
	ssize_t			len;
	t_string		out;
	ssize_t			plen;
	t_fe			fe;
	size_t			sread;

	out.s = NULL;
	out.l = 0;
	len = 0;
	if (yempty_until(&out, &len, rmn, end))
		return (out.s);
	if (!out.s)
		return (NULL);
	plen = len;
	sread = YREAD_SIZE;
	while (yread_input(&out, &len, sread))
	{
		fe = (t_fe){out.s, rmn};
		if (yfind_end(fe, plen, &len, end))
			return (out.s);
		plen = len;
		sread = (2 * sread < YMAX_RDSZ) ? 2 * sread : sread;
	}
	return (out.s);
}

static char				*yread_n(ssize_t n, char *rmn)
{
	ssize_t			len;
	t_string		out;
	t_fe			fe;
	size_t			sread;

	out.s = NULL;
	out.l = 0;
	len = 0;
	if (yempty_n(&out, &len, rmn, n))
		return (out.s);
	if (!out.s)
		return (NULL);
	sread = YREAD_SIZE;
	while (yread_input(&out, &len, sread))
	{
		fe = (t_fe){out.s, rmn};
		if (yfind_n(fe, &len, n))
			return (out.s);
		sread = (2 * sread < YMAX_RDSZ) ? 2 * sread : sread;
	}
	return (out.s);
}

char					*yread(ssize_t n, char *end)
{
	static char		rmn[YMAX_RDSZ + 1];

	if (end != NULL)
		return (yread_until(*end, rmn));
	if (n > 0)
		return (yread_n(n, rmn));
	return (NULL);
}
