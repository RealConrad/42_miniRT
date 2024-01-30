
#include "mini_rt.h"

static void	check_no_light(t_scene *scene);

// void	leak_check(void)
// {
// 	system("leaks miniRT");
// }

int	main(int argc, char *argv[])
{
	t_scene		scene;

	if (argc != 2)
		parser_exit(INPUT_MISSING, NULL);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 3), ".rt", 4) != 0)
		parser_exit(INPUT_FILE, NULL);
	scene = (t_scene){};
	scene = parser(argv);
	check_no_light(&scene);
	render_scene(&scene);
	mlx_loop(scene.mlx);
	return (0);
}

static void	check_no_light(t_scene *scene)
{
	if (!legal_colour(scene->light.colour))
		scene->light.colour = (t_colour){255, 255, 255};
	if (scene->light.light_ratio == -1)
		scene->light.light_ratio = 0;
	if (scene->amb_light.light_ratio == -1)
		scene->amb_light.light_ratio = 0;
	if (!legal_colour(scene->amb_light.colour_in_range))
		scene->amb_light.colour_in_range = (t_colour){0, 0, 0};
}

// atexit(leak_check);