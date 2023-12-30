#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	t_scene		scene;

	if (argc != 2)
		parser_exit(INPUT_MISSING, NULL);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 3), ".rt", 4) != 0)
		parser_exit(INPUT_FILE, NULL);
	scene = (t_scene){};
	scene = parser(argv);
	
	// t_print_scene(scene);
	render_scene(&scene);
	mlx_loop(scene.mlx);
	return (0);
}

