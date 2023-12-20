
#include "mini_rt.h"

void	init_amb(t_scene *scene, char **tokens, int fd)
{
	if (!is_valid_numbers(tokens))
		exit_analize(scene, tokens, fd, NULL);
	scene->amb_light.light_ratio = ft_atof(tokens[1]);
	if (scene->amb_light.light_ratio > 1 || scene->amb_light.light_ratio < 0)
		exit_analize(scene, tokens, fd, NULL);
	assign_colour(&(scene->amb_light.colour_in_range), tokens, 2);
	if (!legal_colour(scene->amb_light.colour_in_range))
		exit_analize(scene, tokens, fd, NULL);
}

void	init_cam(t_scene *scene, char **tokens, int fd)
{
	if (!is_valid_numbers(tokens))
		exit_analize(scene, tokens, fd, NULL);
	assign_vector(&(scene->camera.cords), tokens, 1);
	assign_vector(&(scene->camera.or_vect), tokens, 4);
	scene->camera.fov = ft_atoi(tokens[7]);
	if (legal_vector(scene->camera.or_vect, -1, 1) == false
		|| scene->camera.fov < 0 || scene->camera.fov > 180)
		exit_analize(scene, tokens, fd, NULL);
}

void	init_light(t_scene *scene, char **tokens, int fd)
{
	if (!is_valid_numbers(tokens))
		exit_analize(scene, tokens, fd, NULL);
	assign_vector(&(scene->light.cords), tokens, 1);
	scene->light.light_ratio = ft_atof(tokens[4]);
	if (scene->light.light_ratio > 1 || scene->light.light_ratio < 0)
		exit_analize(scene, tokens, fd, NULL);
	assign_colour(&(scene->light.colour), tokens, 5);
	if (!legal_colour(scene->light.colour))
		exit_analize(scene, tokens, fd, NULL);
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
