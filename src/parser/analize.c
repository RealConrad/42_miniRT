
#include "../../includes/mini_rt.h"

static void	input_amb(char *line, t_scene *scene, int fd);
static void	exit_analize(char *line, t_scene *scene, int fd);

void	analize_line(char *line, t_scene *scene, int fd)
{
	char	**split;
	if (line[0] == '\0' || ft_strncmp(line, "\n", 2) == 0)
		return ;
	else if (line[0] == 'A')
		input_amb(line, scene, fd);
	else if (line[0] == 'C')
		input_cam(line, scene, fd);
	else if (line[0] == 'L')
		input_light(line, scene, fd);
	else if (ft_strncmp(line, "pl", 2) == 0 || ft_strncmp(line, "sp", 2) == 0
		|| ft_strncmp(line, "cy", 2) == 0)
		input_object(line, scene, fd);
	else
		exit_analize(line, scene, fd);
}

static void	input_amb(char *line, t_scene *scene, int fd)
{
	int	i;

	if (line[1] != ' ' && line[1] != '\t')
		exit_analize(line, scene, fd);
	i = 1;
	// while (ft_isblank(line[i]) == 1)
	// 	i++;
	//!Split by whitespaces!
}

static void	exit_analize(char *line, t_scene *scene, int fd)
{
	close(fd);
	free(line);
	free_objects(&(scene->objects));
	parser_exit(FORMAT, NULL);
}
