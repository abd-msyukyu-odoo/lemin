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
//		c_4 = {(n - 3 * (a_44 - a_43) - 2 * (a_43 - a_42) - (a_42 - a_41) [-1-2-3]) / 3}
//		+ {3 * (a_44 - a_43) [+3] / 3}
//		+ {2 * (a_43 - a_42) [+2] / 2}
//		+ {a_42 - a_41 [+1]}
//		+ {a_41 - 1}

static int	compute_x(int a, t_path *p, int nb_paths)
{
	t_path	*last;
	int		rtn;

	last = p;
	while (last->next)
		last = last->next;
	rtn = a;
	rtn += (nb_paths - 1) * (last->nb_elements - 1);
	last = p;
	while (last)
	{
		rtn += last->nb_elements - 1;
		last = last->next;
	}
	return (rtn);
}

int			get_cost(t_path *paths, int nb_paths)
{
	int		minus_one;
	int		x;
	int		cost;
	t_path	*last;

	last = paths;
	while (last->next)
		last = last->next;
	x = compute_x(lemin->nb_ants, pahts, nb_paths);
	minus_one = nb_paths > 1 ? x % (nb_paths - 1) : 0;
	x -= minus_one;
	cost = (x / nb_paths) + (last->nb_elements - 1);
	cost -= (minus_one == 0 ? 1 : 0);
	return (cost);
}