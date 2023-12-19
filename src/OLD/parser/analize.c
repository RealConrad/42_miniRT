
#include "mini_rt.h"

static void	input_cam(char *line, t_scene *scene, int fd, char **split);
static void	input_amb(char *line, t_scene *scene, int fd, char **split);

/**
 * @brief Analizes the input line and calls the respective function, exits on
 * wrong input
 * @param line the input line from the parser
 * @param scene the scene to write to
 * @param fd the open file, only needed to close on exit
 */
void	analize_line(char *line, t_scene *scene, int fd)
{
	char	**split;

	if (line[0] == '\0' || ft_strncmp(line, "\n", 2) == 0)
		return ;
	split = ft_split_blank(line);
	if (split == NULL)
		exit_analize(line, scene, fd, split);
	else if (ft_strncmp(split[0], "A", 2) == 0
		&& scene->amb_light.light_ratio == -1)
		input_amb(line, scene, fd, split);
	else if (ft_strncmp(split[0], "C", 2) == 0 && scene->camera.fov == -1)
		input_cam(line, scene, fd, split);
	else if (ft_strncmp(split[0], "L", 2) == 0
		&& scene->light.light_ratio == -1)
		input_light(line, scene, fd, split);
	else if (ft_strncmp(split[0], "pl", 3) == 0
		|| ft_strncmp(split[0], "sp", 3) == 0
		|| ft_strncmp(split[0], "cy", 3) == 0)
		input_object(line, scene, fd, split);
	else
		exit_analize(line, scene, fd, split);
	free_split(split);
}

/**
 * @brief Inputs the light values, exiting on wrong input
 * @param line the line allocated by the parser, only needed for exiting
 * @param scene the scene to write data to
 * @param fd the file opened in the parser, needed only to close on exit
 * @param split the split containing the data
 */
static void	input_light(char *line, t_scene *scene, int fd, char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 4 && i != 6 && i != 8)
		exit_analize(line, scene, fd, split);
	if (legal_vector_input(split, 1) == false)
		exit_analize(line, scene, fd, split);
	scene->light.cords = get_vector_input(split, 1);
	if (ft_strchr(split[1], ',') != NULL && atof_check(split[2]))
		scene->light.light_ratio = atof(split[2]);
	else if (atof_check(split[4]) == true)
		scene->light.light_ratio = atof(split[4]);
	else
		exit_analize(line, scene, fd, split);
	if (ft_strchr(split[i - 1], ',') != NULL)
		scene->light.colour = get_colour_input(split, i - 3);
	else
		scene->light.colour = get_colour_input(split, i - 1);
	if (legal_colour(scene->light.colour) == false
		|| scene->light.light_ratio < 0.0 || scene->light.light_ratio > 1.0)
		exit_analize(line, scene, fd, split);
}

/**
 * @brief Writes the camera input to the scene and exits on wrong input
 * @param line the line allocated by the parser, only needed for exiting
 * @param scene the scene to write data to
 * @param fd the file opened in the parser, needed only to close on exit
 * @param split the split containing the data
 * 
 */
static void	input_cam(char *line, t_scene *scene, int fd, char **split)
{
	int			i;

	i = 0;
	while (split[i] != NULL)
		i++;
	if (i != 4 && i != 8 && i != 6)
		exit_analize(line, scene, fd, split);
	if (legal_vector_input(split, 1) == false)
		exit_analize(line, scene, fd, split);
	scene->camera.cords = get_vector_input(split, 1);
	if (ft_strchr(split[1], ',') != NULL && legal_vector_input(split, 2))
		scene->camera.or_vect = get_vector_input(split, 2);
	else if (legal_vector_input(split, 4) == true)
		scene->camera.or_vect = get_vector_input(split, 4);
	else
		exit_analize(line, scene, fd, split);
	if (legal_vector(scene->camera.or_vect, -1, 1) == false)
		exit_analize(line, scene, fd, split);
	if (atoi_check(split[i - 1]) == false)
		exit_analize(line, scene, fd, split);
	scene->camera.fov = ft_atoi(split[i - 1]);
	if (scene->camera.fov > 180 || scene->camera.fov < 0)
		exit_analize(line, scene, fd, split);
}

/**
 * @brief Inputs the ambient light values, exiting on wrong input
 * @param line the line allocated by the parser, only needed for exiting
 * @param scene the scene to write data to
 * @param fd the file opened in the parser, needed only to close on exit
 * @param split the split containing the data
 */
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

/**
 * @brief Exits the program and frees all memory
 * @param line the line allocated in the parser
 * @param scene the scene struct containing the allocated objects
 * @param fd the open file to close
 * @param split the splitted line
 */
void	exit_analize(char *line, t_scene *scene, int fd, char **split)
{
	close(fd);
	free(line);
	if (split != NULL)
		free_split(split);
	// free_objects(&(scene->objects));
	parser_exit(FORMAT, NULL);
}
