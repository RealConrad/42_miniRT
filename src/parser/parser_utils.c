#include "mini_rt.h"

void	exit_analize(t_scene *scene, char **tokens, int fd, t_object *object)
{
	if (object->cylinder)
		free(object->cylinder);
	else if (object->plane)
		free(object->plane);
	else if (object->sphere)
		free (object->sphere);
	free(object);
	free_objects(scene->objects);
	close(fd);
	free_2d_array(tokens);
	parser_exit(FORMAT, NULL);
}

