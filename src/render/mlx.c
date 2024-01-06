
#include "mini_rt.h"

void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!scene->mlx)
		exit_render(scene, "mlx_init failed");
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	mlx_key_hook(scene->mlx, (void *)escape, NULL);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
}

void	exit_render(t_scene *scene, char *msg)
{
	free_objects(scene->objects);
	ft_fprintf(2, "Error\n");
	ft_fprintf(2, "%s\n", msg);
	exit(1);
}
