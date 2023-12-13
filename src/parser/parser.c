
#include "../../includes/mini_rt.h"

static void	init_scene(t_scene *scene);

/**
 * @brief takes, checks and converts input
 * @param argc 
 * @param argv 
 * @return the scene struct
 */
t_scene	parser(int argc, char *argv[])
{
	t_scene	scene;
	int		fd;
	char	*line;

	if (argc != 2)
		parser_exit(INPUT_MISSING, NULL);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 3), ".rt", 4) != 0)
		parser_exit(INPUT_FILE, NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		parser_exit(OPEN_FAIL, NULL);
	init_scene(&scene);
	line = get_next_line(fd);
	if (line == NULL)
		parser_exit(MISSING, NULL);
	while (line != NULL)
	{
		analize_line(line, &scene, fd);
		free(line);
		line = get_next_line(fd);
	}
	if (scene.amb_light.light_ratio == -1 || scene.camera.fov == -1
		|| scene.light.light_ratio == -1)
	{
		// free_objects(scene->objects);
		parser_exit(MISSING, NULL);
	}
	return (scene);
}

static void	init_scene(t_scene *scene)
{
	scene->amb_light.light_ratio = -1;
	scene->camera.fov = -1;
	scene->light.light_ratio = -1;
}

/**
 * @brief Cleanly exits the parser
 * @param error_code the code for the exit message
 * @param free_me NULLABLE, for freeing allocated memory 
 * takes an unallocated array
 */
void	parser_exit(int error_code, void **free_me)
{
	int	i;

	i = -1;
	if (free_me != NULL)
	{
		while (free_me[++i] != NULL)
			free(free_me[i]);
	}
	if (error_code == NORMAL)
		exit(0);
	ft_fprintf(2, "Error\n");
	if (error_code == MALLOC_FAIL)
		ft_fprintf(2, "Malloc fail in parser\n");
	else if (error_code == OPEN_FAIL)
		ft_fprintf(2, "Open fail in parser, make sure file exists\n");
	else if (error_code == INPUT_FILE)
		ft_fprintf(2, "Input file isn't a .rt file\n");
	else if (error_code == DUPLICATED)
		ft_fprintf(2, "A, L or C duplicated\n");
	else if (error_code == MISSING)
		ft_fprintf(2, " A, L or C is missing\n");
	else if (error_code == INPUT_MISSING)
		ft_fprintf(2, "Wront input, please only provide a .rt file\n");
	else if (error_code == FORMAT)
		ft_fprintf(2, "Wrong input format\n");
	exit(1);
}
