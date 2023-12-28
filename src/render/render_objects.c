#include "mini_rt.h"

void	render_cylinder(t_scene *scene, t_cylinder *cylinder)
{
	(void)cylinder;
	(void)scene;
}

void	render_plane(t_scene *scene, t_plane *plane)
{
	(void)plane;
	(void)scene;
}

void	render_sphere(t_scene *scene, t_sphere *sphere)
{
	int			x;
	int			y;
	uint32_t	colour;
	
	y = -sphere->diameter / 2;
	colour = get_rgb(sphere->colour);
	while (y <= sphere->diameter / 2)
	{
		x = -sphere->diameter / 2;
		while (x <= sphere->diameter / 2)
		{
			if (((x * x) + (y * y)) <= ((sphere->diameter / 2) * (sphere->diameter / 2)))
				mlx_put_pixel(scene->img, sphere->cords.x + x, sphere->cords.y + y, colour);
			x++;
		}
		y++;
	}
}
