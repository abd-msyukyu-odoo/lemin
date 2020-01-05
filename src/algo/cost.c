#include "lemin.h"

//	Meilleure repartition des fourmis :
//	Soient :
//		  n		: nombre de fourmis
//			i		: nombre de chemins
//			c_i		: nombre de coups
//			a_ix	: nombre d'aretes du chemin x
//
//	i = 1
//		c_1 = {n}				# fourmis dans le chemin
//		+ {a_11 - 1}			# fin du parcours du chemin par la derniere fourmi
//	i = 2
//		c_2 = {(n - (a_22 - a_21) [-1]) / 2} 	# fourmis dans les 2 chemins
//		+ {a_22 - a_21 [+1]} 				# fourmis supplementaires dans le chemin plus court
//		+ {a_21 - 1}						# fin du parcours du petit chemin par la derniere fourmi
//		#[] a adapter pour que la division soit entiere
//		#si a_22 - a_21 >= n - 1 : on conserve la solution pour i - 1
//	i = 3
//		c_3 = {(n - 2 * (a_33 - a_32) - (a_32 - a_31) [-1-2]) / 3}	# fourmis dans les 3 chemins
//		+ {2 * (a_33 - a_32) [+2] / 2}							# fourmis dans les 2 plus courts chemins
//		+ {a_32 - a_31 [+1]}									# fourmis dans le plus court chemin
//		+ {a_31 - 1}											# fin du parcours du petit chemin par la derniere fourmi
//	i = 4
//		c_4 = {(n - 3 * (a_44 - a_43) - 2 * (a_43 - a_42) - (a_42 - a_41) [-1-2-3]) / 4}
//		+ {3 * (a_44 - a_43) [+3] / 3}
//		+ {2 * (a_43 - a_42) [+2] / 2}
//		+ {a_42 - a_41 [+1]}
//		+ {a_41 - 1}

static t_path   *get_path_min_bridge(t_path *p)
{
	t_path  *min;

	min = p;
	while ((p = p->next))
		if (p->size < min->size)
			min = p;
	return (min);
}

int             get_cost(void)
{
	t_path  *min;

	set_nb_ants();
	min = get_path_min_bridge(lemin->paths->first);
	return (min->n_ants + min->size);
}

static int  get_max_bridge(t_path *p)
{
	int length;

	length = p->size;
	while ((p = p->next))
		if (p->size > length)
			length = p->size;
	return (length);
}

static void	set_nb_ants_while2(int *max, int *nb_ants, t_path **curr,
	int *nb_path)
{
	if (*nb_ants % *nb_path > 0)
		*max = (*nb_ants / *nb_path) + 1;
	else
		*max = *nb_ants / *nb_path;
	(*curr)->n_ants += *max;
	*nb_ants -= *max;
	(*nb_path)--;
	*curr = (*curr)->next;
}

void        set_nb_ants(void)
{
	int     max;
	t_path  *p;
	int     nb_ants;
	t_path  *curr;
	int     nb_path;

	nb_path = 0;
	p = lemin->paths->first;
	max = get_max_bridge(p);
	curr = p;
	nb_ants = lemin->n_ants;
	while (curr)
	{
		nb_path++;
		curr->n_ants = max - curr->size;
		nb_ants -= curr->n_ants;
		curr = curr->next;
	}
	curr = p;
	while (curr && nb_ants)
		set_nb_ants_while2(&max, &nb_ants, &curr, &nb_path);
}
