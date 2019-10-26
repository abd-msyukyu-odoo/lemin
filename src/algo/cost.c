#include "lemin.h"


//	Meilleure repartition des fourmis :
//	Soient :
//	      n		: nombre de fourmis
//			i		: nombre de chemins
//			c_i		: nombre de coups
//			a_ix	: nombre d'aretes du chemin x
//
//	i = 1
//		c_1 = {n}				# fourmis dans le chemin
//		+ {a_11 - 1}		    # fin du parcours du chemin par la derniere fourmi
//	i = 2
//	    c_2 = {(n - (a_22 - a_21) [-1]) / 2} 	# fourmis dans les 2 chemins
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

static int  compute_x(int a, t_array *p)
{
	int     rtn;
	int     i;

	rtn = a;
	rtn += (p->n_items - 1) * (((t_array *)ft_array_get(p, p->n_items - 1))->n_items - 1);
	i = 0;
	while (i < p->n_items - 1)
	{
		rtn += (((t_array *)ft_array_get(p, p->n_items - 1))->n_items - 1);
		i++;
	}
	return rtn;
}

int     get_cost(t_array *paths, int ants)
{
	int     minus_one;
	int     x;
	int     cost;

	x = compute_x(ants, paths);
	minus_one = paths->n_items > 1 ? x % (paths->n_items - 1) : 0;
	x -= minus_one;
	cost = (x / paths->n_items) + (((t_array *)ft_array_get(p, p->n_items - 1))->n_items - 1);
	cost -= (minus_one == 0 ? 1 : 0);
	return (cost);
}