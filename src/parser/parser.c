#include "mini_rt.h"

static void	analize_line(t_scene *scene, char **tokens, int fd);
static void	init_scene_default(t_scene *scene);

t_scene	parser(int argc, char **argv)
{
	t_scene	scene;
	int		fd;
	char	*line;
	char	**tokens;

	if (argc != 2)
		parser_exit(INPUT_MISSING, NULL);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 3), ".rt", 4) != 0)
		parser_exit(INPUT_FILE, NULL);
	fd = open(argv[1], O_RDONLY);
	init_scene_default(&scene);
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		tokens = split_line(line);
		free(line);
		if (!tokens)
			parser_exit(MALLOC_FAIL, NULL);
		analize_line(&scene, tokens, fd);
		free_2d_array(tokens);
	}
	return (close(fd), scene);
}

static void	analize_line(t_scene *scene, char **tokens, int fd)
{
	int	i;

	i = 0;
	while (tokens[i])
		i++;
	if (i == 5 && ft_strncmp(tokens[0], "A", 2) == 0)
		init_amb(scene, tokens, fd);
	else if (i == 8 && ft_strncmp(tokens[0], "C", 2) == 0)
		init_cam(scene, tokens, fd);
	else if (i == 8 && ft_strncmp(tokens[0], "L", 2) == 0)
		init_light(scene, tokens, fd);
	else if (i == 10 && ft_strncmp(tokens[0], "pl", 3) == 0)
		init_plane(scene, tokens, fd);
	else if (i == 8 && ft_strncmp(tokens[0], "sp", 3) == 0)
		init_sphere(scene, tokens, fd);
	else if (i == 12 && ft_strncmp(tokens[0], "cy", 3) == 0)
		init_cylinder(scene, tokens, fd);
	else
		exit_analize(scene, tokens, fd, NULL);
}

static void	init_scene_default(t_scene *scene)
{
	scene->amb_light.light_ratio = -1;
	scene->camera.fov = -1;
	scene->light.light_ratio = -1;
	scene->objects = NULL;
}

void	parser_exit(int error_code, void **free_me)
{
	int	i;

	i = -1;
	if (free_me != NULL)
		while (free_me[++i] != NULL)
			free(free_me[i]);
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
