#ifndef BFS_H
#define BFS_H

//TODO: add bfs_visited to room elem / default = 0
//TODO: add bfs_level to room element / default = -1

typedef struct	s_bfs_room
{
	struct s_bfs_room	*next;
	struct s_bfs_room	*previous;
    t_room		        *room;
}				t_bfs_room;

typedef struct	s_floor
{
    struct s_floor		*next;
    struct s_floor		*previous;
    int			        level;
    t_bfs_room	        *rooms;
}				t_floor;


/*
** bfs_tools
*/
void    bfs_add_room(t_floor *floor, t_room *elem, t_global *g);
t_floor *bfs_add_floor(t_floor *floor, t_global *g);
void	bfs_delete_floor(t_bfs_room **room);
void	bfs_delete_bfs(t_floor **floor);

#endif
