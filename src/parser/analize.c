
#include "mini_rt.h"

static void	input_cam(char *line, t_scene *scene, int fd, char **split);
static void	input_amb(char *line, t_scene *scene, int fd, char **split);
static void	exit_analize(char *line, t_scene *scene, int fd, char **split);

void	analize_line(char *line, t_scene *scene, int fd)
{
	char	**split;

	if (line[0] == '\0' || ft_strncmp(line, "\n", 2) == 0)
		return ;
	split = ft_split_blank(line);
	if (split == NULL)
		exit_analize(line, scene, fd, split);
	else if (ft_strncmp(split[0], "A", 2) == 0)
		input_amb(line, scene, fd, split);
	else if (ft_strncmp(split[0], "C", 2) == 0)
		input_cam(line, scene, fd, split);
	// else if (ft_strncmp(split[0], "L", 2) == 0)
	// 	input_light(line, scene, fd);
	// else if (ft_strncmp(split[0], "pl", 3) == 0
	// 	|| ft_strncmp(split[0], "sp", 3) == 0
	// 	|| ft_strncmp(split[0], "cy", 3) == 0)
	// 	input_object(line, scene, fd);
	else
		exit_analize(line, scene, fd, split);
	free_split(split);
}

static void	input_cam(char *line, t_scene *scene, int fd, char **split)
{
	int			i;

	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 4 && i != 8)
		exit_analize(line, scene, fd, split);
	if (legal_vector_input(split, 1) == false)
		exit_analize(line, scene, fd, split);
	scene->camera.cords = get_vector_input(split, 1);
	if (ft_strchr(split[1], ',') == NULL && legal_vector_input(split, 2))
		scene->camera.or_vect = get_vector_input(split, 2);
	else if (legal_vector_input(split, 4) == true)
		scene->camera.or_vect = get_vector_input(split, 4);
	else
		exit_analize(line, scene, fd, split);
	if (legal_vector(scene->camera.or_vect, -1, 1) == false)
		exit_analize(line, scene, fd, split);
	if (atoi_check(split[i -1]) == false)
		exit_analize(line, scene, fd, split);
	scene->camera.fov = ft_atoi(split[i -1]);
	if (scene->camera.fov > 180 || scene->camera.fov < 0)
		exit_analize(line, scene, fd, split);
}

static void	input_amb(char *line, t_scene *scene, int fd, char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 3 && i != 5)
		exit_analize(line, scene, fd, split);
	if (atof_check(split[1]) == false)
		exit_analize(line, scene, fd, split);
	scene->amb_light.light_ratio = ft_atof(split[1]);
	if (scene->amb_light.light_ratio > 1 || scene->amb_light.light_ratio < 0)
		exit_analize(line, scene, fd, split);
	scene->amb_light.colour_in_range = get_colour_input(split, 2);
	if (legal_colour(scene->amb_light.colour_in_range) == false)
		exit_analize(line, scene, fd, split);
}

static void	exit_analize(char *line, t_scene *scene, int fd, char **split)
{
	close(fd);
	free(line);
	if (split != NULL)
		free_split(split);
	free_objects(&(scene->objects));
	parser_exit(FORMAT, NULL);
}
