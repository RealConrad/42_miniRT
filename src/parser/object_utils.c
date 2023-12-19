#include "mini_rt.h"

void	add_object_to_linked_list(t_scene *scene, t_object *object)
{
	t_object	*temp;

	if (!scene->objects)
		scene->objects = object;
	else
	{
		temp = scene->objects;
		while (temp->next)
			temp = temp->next;
		temp->next = object;
	}
}
