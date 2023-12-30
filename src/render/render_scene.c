#include "mini_rt.h"

static t_viewport	calculate_viewport(t_scene *scene);
static void			calculate_ray_and_draw(t_scene *scene, t_viewport viewport, int y, int x);

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_viewport	viewport;

	y = 0;
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!scene->mlx)
		exit(1); // Change this to error function and clean up everything
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	mlx_key_hook(scene->mlx, (void *)escape, NULL);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
	viewport = calculate_viewport(scene);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculate_ray_and_draw(scene, viewport, y, x);
			x++;
		}
		y++;
	}
}

static void	calculate_ray_and_draw(t_scene *scene, t_viewport viewport, int y, int x)
{
	t_ray		ray;
	t_vector	ray_direction;
	t_colour	pixel_colour;
	double		u;
	double		v;

	u = (double)x / (WIDTH - 1) * 2 - 1;
	v = (double)y / (HEIGHT - 1) * 2 - 1;
	ray_direction = vec_add(vec_add(viewport.lower_left_corner, vec_multiply(viewport.horizontal, (t_vector){u, u, u})), vec_multiply(viewport.vertical, (t_vector){v, v, v}));
	ray_direction = vec_subtract(ray_direction, scene->camera.cords);

	ray.origin = scene->camera.cords;
	ray.direction = ray_direction;
	pixel_colour = get_ray_colour(ray, scene->objects);
	mlx_put_pixel(scene->img, x, y, get_rgb(pixel_colour));
}

static t_viewport	calculate_viewport(t_scene *scene)
{
	t_viewport	viewport;
	double		vp_height;
	double		vp_width;

	vp_height = 2.0 * tan((scene->camera.fov * (M_PI / 180.0)) / 2.0);
	vp_width = vp_height * ((double)WIDTH / (double)HEIGHT);
	viewport.camera_direction = normalize_vector(scene->camera.or_vect);
	viewport.horizontal = (t_vector){vp_width, 0, 0};
	viewport.vertical = (t_vector){0, vp_height, 0};
	viewport.lower_left_corner = vec_subtract(
		vec_subtract(
			vec_subtract(scene->camera.cords, 
						vec_divide(viewport.horizontal, (t_vector){2, 2, 2})),
			vec_divide(viewport.vertical, (t_vector){2, 2, 2})), 
		viewport.camera_direction);

	return (viewport);
}
