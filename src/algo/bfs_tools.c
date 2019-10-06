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
    return (new);
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
}