#include "mini_rt.h"

static t_viewport	calculate_viewport(t_scene *scene);
static void			calculate_ray_and_draw(t_scene *scene, t_viewport viewport, int y, int x);
static void			assign_viewport_vectors(t_viewport *viewport, t_scene *scene, double vp_height, double vp_width);

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

static void	calculate_ray_and_draw(t_scene *scene, t_viewport viewport, int y, int x) {
	t_ray		ray;
	t_colour	pixel_colour;
	t_vector	u;
	t_vector	v;
	t_vector	pixel_center;

	u = vec_divide(viewport.horizontal, (t_vector){WIDTH, WIDTH, WIDTH});
	v = vec_divide(viewport.vertical, (t_vector){HEIGHT, HEIGHT, HEIGHT});
	// Get center pos of x,y in 3D worldd :)))))
	pixel_center = vec_add(viewport.pixel00_loc, vec_add(vec_multiply(u, (t_vector){x, x, x}), vec_multiply(v, (t_vector){y, y, y})));

	ray.origin = scene->camera.cords;
	ray.direction = normalize_vector(vec_subtract(pixel_center, scene->camera.cords));
	pixel_colour = get_ray_colour(ray, scene->objects);
	mlx_put_pixel(scene->img, x, y, get_rgb(pixel_colour));
}

static t_viewport calculate_viewport(t_scene *scene)
{
	t_viewport	viewport;
	double		vp_height;
	double		vp_width;

	vp_height = 2.0 * tan((scene->camera.fov * (M_PI / 180.0)) / 2.0);
	vp_width = vp_height * ((double)WIDTH / (double)HEIGHT);
	assign_viewport_vectors(&viewport, scene, vp_height, vp_width);
	return (viewport);
}

static void	assign_viewport_vectors(t_viewport *viewport, t_scene *scene, double vp_height, double vp_width)
{
	t_vector	backward;
	t_vector	pixel_delta_u;
	t_vector	pixel_delta_v;
	double		focal_length;

	focal_length = 1.0;
	viewport->camera_direction = normalize_vector(scene->camera.or_vect);
	viewport->horizontal = (t_vector){vp_width, 0, 0};
	viewport->vertical = (t_vector){0, -vp_height, 0};
	// Get lower upper corner
	backward = vec_multiply(viewport->camera_direction, (t_vector){-focal_length, -focal_length, -focal_length});
	viewport->upper_left_corner = vec_add(scene->camera.cords, backward);
	viewport->upper_left_corner = vec_subtract(viewport->upper_left_corner, vec_divide(viewport->horizontal, (t_vector){2, 2, 2}));
	viewport->upper_left_corner = vec_subtract(viewport->upper_left_corner, vec_divide(viewport->vertical, (t_vector){2, 2, 2}));
	// Get first pixel (0,0) in viewport
	pixel_delta_u = vec_divide(viewport->horizontal, (t_vector){WIDTH, WIDTH, WIDTH});
	pixel_delta_v = vec_divide(viewport->vertical, (t_vector){HEIGHT, HEIGHT, HEIGHT});
	viewport->pixel00_loc = vec_add(viewport->upper_left_corner, vec_multiply(vec_add(pixel_delta_u, pixel_delta_v), (t_vector){0.5, 0.5, 0.5}));
}
