
#include "../../includes/mini_rt.h"

void	free_objects(t_object **objects)
{
	t_object	*next;
	t_object	*current;

	if (*objects == NULL)
		return ;
	current = *objects;
	next = current->next;
	while (current != NULL)
	{
		if (current->sphere != NULL)
			free(current->sphere);
		if (current->plane != NULL)
			free(current->plane);
		if (current->cylinder != NULL)
			free(current->cylinder);
		free(current);
		current = next;
		next = current->next;
	}
	*objects = NULL;
}
