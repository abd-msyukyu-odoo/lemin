#include <stdlib.h>
#include <stdio.h>
#include "room.h"
#include "tube.h"
#include "array.h"
#include "btree.h"
#include <time.h>

//gcc -o minimalloc _minimalloc.c ../src/structs/room.c ../src/structs/tube.c ../src/structs/array.c ../src/structs/btree.c -I../includes -I../libft -L../libft/ -lft

int					main(void)
{
	static void		*ptr[1000000];
	clock_t			t1;
	clock_t			t2;

	t1 = clock();
	for (int i = 0; i < 1000000; i++)
		ptr[i] = malloc(sizeof(t_room));
	t2 = clock();
	printf("%f\n", (float)(t2 - t1) / CLOCKS_PER_SEC);
	t1 = clock();
	for (int i = 0; i < 1000000; i++)
		free(ptr[i]);
	t2 = clock();
	printf("%f\n", (float)(t2 - t1) / CLOCKS_PER_SEC);
	return (0);
}
