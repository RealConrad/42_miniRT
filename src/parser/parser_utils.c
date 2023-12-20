#include "mini_rt.h"

void	exit_analyse(t_scene *scene, char **tokens, int fd, t_object *object)
{
	if (object)
	{
		if (object->cylinder)
			free(object->cylinder);
		else if (object->plane)
			free(object->plane);
		else if (object->sphere)
			free (object->sphere);
		free(object);
	}
	free_objects(scene->objects);
	close(fd);
	free_2d_array(tokens);
	parser_exit(FORMAT, NULL);
}

void	assign_vector(t_vector *vector, char **tokens, int start_index)
{
	vector->x = ft_atof(tokens[start_index]);
	vector->y = ft_atof(tokens[start_index + 1]);
	vector->z = ft_atof(tokens[start_index + 2]);
}

void	assign_colour(t_colour *colour, char **tokens, int start_index)
{
	colour->r = ft_atoi(tokens[start_index]);
	colour->g = ft_atoi(tokens[start_index + 1]);
	colour->b = ft_atoi(tokens[start_index + 2]);
}
