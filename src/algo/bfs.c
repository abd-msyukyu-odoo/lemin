
#include "lemin.h"

void    bfs_add_room(t_floor *floor, t_room *elem, t_global *g)
{
	t_bfs_room	*current;
	t_bfs_room	*new;

	current = floor->rooms;
	while (current && current->next)
		current = current->next;
	if (!(new = (t_bfs_room *)malloc(sizeof(t_bfs_room))))
		return (print(destroy_global(g)));
	new->room = elem;
	new->next = NULL;
	new->previous = current;
	if (current)
		current->new;
	else
		floor->rooms = new;
}

t_floor *bfs_add_floor(t_floor *floor, t_global *g)
{
	t_floor     *new;

	if(!(new = (t_floor)malloc(sizeof(t_floor))))
		return (print(destroy_global(g)));
	while (floor && floor->next)
		floor = floor->next;
	new->previous = floor;
	new->rooms = NULL;
	new->next = NULL;
	if (floor)
	{
		floor->next = new;
		new->level = floor->level + 1;
	}
	else
		new->level = 0;
	return (new);a  a
}

void	bfs_delete_floor(t_bfs_room **room)
{
	if ((*room)->next)
		bfs_delete_floor(&(room->next));
	(*room)->previous = NULL;
	free(*room);
}

void	bfs_delete_bfs(t_floor **floor)
{
	if ((*floor)->next)
		bfs_delete_bfs(&(*floor->next));
	if ((*floor)->rooms)
		bfs_delete_floor(&((*floor)->rooms));
	free(floor);


void    bfs_add_room_to_pyramid(t_room *room, t_floor *floor, int depth,
        t_global *g)
{
    if (!floor)
        floor = bfs_add_floor(floor, g);
    while (floor->level != depth)
    {
        if (floor->level > depth)
            floor = floor->previous;
        else if (floor->next)
            floor = floor->next;
        else
            floor = bfs_add_floor(floor, g);
    }
    bfs_add_room(floor, room, g);
}

void    make_pyramid(t_room *room, t_global *g)
{
    int i;

    if (room->bfs_visited)
        return ;
    room->bfs_visited = 1;
    bfs_add_room_to_pyramid(room, lemin->bfs, room->bfs_level, g);
    i = room->a_tubes->size + 1;//TODO: verifier le parametre
    while (--i >= 0)
        make_pyramid(ft_tube_get_connection((t_tube *)
        ft_array_get(room->a_tubes, i), room), g);
}

void    set_level(t_room *room, int depth)
{
    int i;

    if (room->bfs_level == -1 || room->bfs_level > depth)
        room->bfs_level = depth;
    else
        return ;
    i = room->a_tubes->size + 1;//TODO: verifier le parameter
    while (--i >= 0)
        set_level(ft_tube_get_connection((t_tube *)
        ft_array_get(room->a_tubes, i), room), depth + 1);
}

void    bfs()
{
    t_room  *start;

    start = lemin->start;
    set_level(start, 0);
    make_pyramid(start, g);
}