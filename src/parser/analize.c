
#include "../../includes/mini_rt.h"

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
	// else if (ft_strncmp(split[0], "C", 2) == 0)
	// 	input_cam(line, scene, fd);
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
