# include "lemin.h"

void        remove_ant(t_ant **address, t_ant *actual)
{
	*address = actual->next;
	actual->next = NULL;
	free(actual->key);
	if (ft_memanager_refill(lemin->mmng, (void *)actual) != 1) // TODO ajuster chiffre
		return (lemin_error(LEMIN_ERR_PRINT));
}


t_ant       *add_ant(t_ant *a_list, int nb, t_p_elem *elem)
{
	t_ant   *new;

	if (!(new = (t_ant *)ft_memanager_get(lemin->mmng, sizeof(t_ant))) ||
		!(new->key = ft_itoa(nb)))
	{
		lemin_error(LEMIN_ERR_PRINT);
		return (NULL);
	}
	new->elem = elem;
	new->next = a_list;
	return (new);
}