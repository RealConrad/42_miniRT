#include "mini_rt.h"

/**
 * @brief Exits the program and cleansup any memory.
 * @param scene The scene which holds the objects to be freed
 * @param tokens An array of strings that need to be freed
 * @param fd The scene file descriptor to be closed
 * @param object Object to be freed.
 */
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

/**
 * @brief Assigns the the vector properties for the given `vector`
 * stored in `tokens`.
 * @param vector The vector struct to assign data to.
 * @param tokens An array of strings containing the data.
 * @param start_index The start index used for the `tokens`.
 * The 3 positions (x, y, z) should be stored in tokens consecutively.
 */
void	assign_vector(t_vector *vector, char **tokens, int start_index)
{
	vector->x = ft_atof(tokens[start_index]);
	vector->y = ft_atof(tokens[start_index + 1]);
	vector->z = ft_atof(tokens[start_index + 2]);
}

/**
 * @brief Assigns the the colour properties for the given `colour`
 * stored in `tokens`.
 * @param colour The colour struct to assign data to.
 * @param tokens An array of strings containing the data.
 * @param start_index The start index used for the `tokens`.
 * The 3 colours (red, green, blue) should be stored in tokens consecutively.
 */
void	assign_colour(t_colour *colour, char **tokens, int start_index)
{
	colour->r = ft_atoi(tokens[start_index]);
	colour->g = ft_atoi(tokens[start_index + 1]);
	colour->b = ft_atoi(tokens[start_index + 2]);
}
