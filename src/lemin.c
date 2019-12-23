#include "lemin.h"

t_global	*lemin = NULL;

int     main(void)
{
	global_construct();
	global_construct_hashmap_rooms(LEMIN_DEFAULT_ROOMS_COUNT);
	ft_printf("construct global done\n");
	read_lemin();
	ft_printf("reading done\n");
	algo();
	ft_printf("algo done\n");
	return (0);
}