/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:28:13 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:47:31 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Exits the program and cleansup any memory. This function
 * is only used for the parser.
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
 * @note The 3 positions (x, y, z) should be stored in tokens consecutively.
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
 * @note The 3 colours (red, green, blue) should be stored in
 * tokens consecutively.
 */
void	assign_colour(t_colour *colour, char **tokens, int start_index)
{
	colour->r = ft_atoi(tokens[start_index]);
	colour->g = ft_atoi(tokens[start_index + 1]);
	colour->b = ft_atoi(tokens[start_index + 2]);
}

/**
 * @brief Checks if the vector is legal
 * @param vector the vector to check
 * @param min the minimal value
 * @param max the max value
 * @return true if in range, false
 */
bool	legal_vector(t_vector vector, double min, double max)
{
	if (vector.x < min || vector.x > max)
		return (false);
	if (vector.y < min || vector.y > max)
		return (false);
	if (vector.z < min || vector.z > max)
		return (false);
	return (true);
}
