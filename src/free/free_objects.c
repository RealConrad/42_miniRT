#include "mini_rt.h"

/**
 * @brief Frees a linked list of objects.
 * @param objects The head node of the object linked list.
 */
void	free_objects(t_object *objects)
{
	t_object	*temp;

	while (objects)
	{
		temp = objects->next;
		if (objects->cylinder)
			free(objects->cylinder);
		else if (objects->plane)
			free(objects->plane);
		else if (objects->sphere)
			free (objects->sphere);
		free(objects);
		objects = temp;
	}
}

