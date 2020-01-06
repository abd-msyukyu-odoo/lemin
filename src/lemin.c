#include "lemin.h"

t_global	*lemin = NULL;

int			main(void)
{
	global_construct();
	global_construct_hashmap_rooms(LEMIN_DEFAULT_ROOMS_COUNT);
	read_lemin();
	algo();
	print();
	return (0);
}
