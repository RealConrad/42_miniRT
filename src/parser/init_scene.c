#include "mini_rt.h"

void	init_amb(t_scene *scene, char **tokens, int fd)
{
	if (!is_valid_numbers(tokens))
		exit_analize(scene, tokens, fd);
	scene->amb_light.light_ratio = ft_atof(tokens[1]);
	if (scene->amb_light.light_ratio > 1 || scene->amb_light.light_ratio < 0)
		exit_analize(scene, tokens, fd);
	scene->amb_light.colour_in_range.r = ft_atoi(tokens[2]);
	scene->amb_light.colour_in_range.g = ft_atoi(tokens[3]);
	scene->amb_light.colour_in_range.b = ft_atoi(tokens[4]);
	if (!legal_colour(scene->amb_light.colour_in_range))
		exit_analize(scene, tokens, fd);
}

void	init_cam(t_scene *scene, char **tokens, int fd)
{
	if (!is_valid_numbers(tokens) || ft_atoi(tokens[7]) > 180
		|| ft_atoi(tokens[7]) < 0)
		exit_analize(scene, tokens, fd);
	scene->camera.cords.x = ft_atof(tokens[1]);
	scene->camera.cords.y = ft_atof(tokens[2]);
	scene->camera.cords.z = ft_atof(tokens[3]);
	scene->camera.or_vect.x = ft_atof(tokens[4]);
	scene->camera.or_vect.y = ft_atof(tokens[5]);
	scene->camera.or_vect.z = ft_atof(tokens[6]);
	scene->camera.fov = ft_atoi(tokens[7]);
}

void	init_light(t_scene *scene, char **tokens, int fd)
{
	if (!is_valid_numbers(tokens))
		exit_analize(scene, tokens, fd);
	scene->light.cords.x = ft_atof(tokens[1]);
	scene->light.cords.y = ft_atof(tokens[2]);
	scene->light.cords.z = ft_atof(tokens[3]);
	scene->light.light_ratio = ft_atof(tokens[4]);
	scene->light.colour.r = ft_atoi(tokens[5]);
	scene->light.colour.g = ft_atoi(tokens[6]);
	scene->light.colour.b = ft_atoi(tokens[7]);
	if (!legal_colour(scene->light.colour))
		exit_analize(scene, tokens, fd);
}
