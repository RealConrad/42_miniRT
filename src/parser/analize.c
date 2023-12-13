
#include "../../includes/mini_rt.h"

static void	input_amb(char *line, t_scene *scene, int fd);

void	analize_line(char *line, t_scene *scene, int fd)
{
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
	{
		close(fd);
		free_objects(&(scene->objects));
		parser_exit(FORMAT, NULL);
	}
}

static void	input_amb(char *line, t_scene *scene, int fd)
{
	if (line[1] != ' ' && line[1] != '\t')

}

static void	exit_analize