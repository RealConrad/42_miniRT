#include "mini_rt.h"

// static void	render_objects(t_scene *scene);

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_ray		ray;
	t_colour	pixel_colour;
	double	u;
	double	v;

	y = 0;
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!scene->mlx)
		exit(1); // Change this to error function and clean up everything
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	mlx_key_hook(scene->mlx, (void *)escape, NULL);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = (double)x / (WIDTH - 1) * 2 - 1;
			v = (double)y / (HEIGHT - 1) * 2 - 1;
			ray.origin = scene->camera.cords;
			ray.direction = (t_vector){u, v, -1};
			pixel_colour = get_ray_colour(ray);
			mlx_put_pixel(scene->img, x, y, get_rgb(pixel_colour));
			x++;
		}
		y++;
	}
}

// static void	render_objects(t_scene *scene)
// {
// 	t_object	*temp;

// 	temp = scene->objects;
// 	if (!temp)
// 		return ;
// 	while (temp)
// 	{
// 		if (temp->cylinder)
// 			render_cylinder(scene, temp->cylinder);
// 		else if (temp->plane)
// 			render_plane(scene, temp->plane);
// 		else if (temp->sphere)
// 			render_sphere(scene, temp->sphere);
// 		temp = temp->next;
// 	}
// }
