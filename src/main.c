#include "mini_rt.h"

int	main(int argc, char *argv[])
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	(void)argc;
	(void)argv;
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (mlx == NULL)
		return (1);
	img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_loop(mlx);
	return (0);
}
