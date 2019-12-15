/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ant.h											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: pierre <pierre@student.42.fr>			  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/07/13 11:34:02 by pierre			#+#	#+#			 */
/*   Updated: 2019/07/15 08:14:46 by pvanderl		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef ANT_H
# define ANT_H

typedef struct		s_ant
{
	struct s_ant	*next;
	t_p_elem		*actual_room;
	char			*key;
}					t_ant;

t_ant				*add_ant(t_ant *ant, int nb, t_p_elem *elem);
void				new_ant(t_ant **ants, char *key);
t_ant				*free_ant(t_ant *a);
void				remove_ant(t_ant **address, t_ant *a);

#endif
