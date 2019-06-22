/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvanderl <pvanderl@students.s19.be>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:18:14 by pvanderl          #+#    #+#             */
/*   Updated: 2018/10/19 14:28:28 by pvanderl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		getlen(char const *s, char c)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i])
	{
		i++;
		n++;
	}
	return (n);
}

static int		getstrn(char const *s, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] && s[i] != c)
			n++;
		while (s[i] != c && s[i])
			i++;
	}
	return (n);
}

static void		split_free(char **out)
{
	int i;

	i = 0;
	while (out[i])
	{
		free(out[i]);
		i++;
	}
	free(out);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**out;

	if (!s || !(out = (char **)malloc(sizeof(*out) * (getstrn(s, c) + 1))))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < getstrn(s, c))
	{
		k = 0;
		if (!(out[i] = ft_strnew(getlen(&s[j], c) + 1)))
		{
			out[i] = NULL;
			split_free(out);
			return (NULL);
		}
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j])
			out[i][k++] = s[j++];
	}
	out[i] = 0;
	return (out);
}
