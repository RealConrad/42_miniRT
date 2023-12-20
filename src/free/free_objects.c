#include "mini_rt.h"

void	free_objects(t_object *objects)
{
	t_object	*temp;

	temp = objects;
	while (temp)
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

