
#include "lemin.h"

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
    bfs_add_room_to_pyramid(room, g->bfs, room->bfs_level, g);
    i = room->a_tubes->size + 1;//TODO: verifier le parameter
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

void    start(t_global *g)
{
    t_room  *start;

    start = g->start;
    set_level(start, 0);
    make_pyramid(start, g);
}