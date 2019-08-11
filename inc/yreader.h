/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yreader.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 10:16:53 by dabeloos          #+#    #+#             */
/*   Updated: 2019/04/17 10:16:55 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef YREADER_H
# define YREADER_H

# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# ifndef YREAD_SIZE
#  define YREAD_SIZE 256
# endif
# ifndef YMAX_RDSZ
#  define YMAX_RDSZ 1000000
# endif
# ifndef YINPUT
#  define YINPUT 0
# endif

/*
** s : string
** l : sizeof s
*/
typedef struct			s_string
{
	char				*s;
	ssize_t				l;
}						t_string;

/*
** out : output string
** rmn : remain string
*/
typedef struct			s_find_end
{
	char				*out;
	char				*rmn;
}						t_fe;

/*
** str_realloc_join.c
*/
unsigned char			ystr_over_realloc(t_string *in, ssize_t old,
							ssize_t new);
ssize_t					ystr_join(t_string *des, ssize_t ld, char *src,
							ssize_t ls);

/*
** remain_editor.c
*/
unsigned char			yempty_until(t_string *out, ssize_t *len, char *rmn,
							char end);
unsigned char			yempty_n(t_string *out, ssize_t *len, char *rmn,
							ssize_t n);
unsigned char			yfind_end(t_fe fe, ssize_t plen, ssize_t *len,
							char end);
unsigned char			yfind_n(t_fe fe, ssize_t *len, ssize_t n);

/*
** reader.c
*/
char					*yread(ssize_t n, char *end);

#endif
