#include "mini_rt.h"

static t_viewport	calculate_viewport(t_scene *scene);
static void			calculate_ray_and_draw(t_scene *scene, t_viewport viewport, int y, int x);
static void			assign_viewport_vectors(t_viewport *viewport, t_scene *scene, double vp_height, double vp_width);

/**
 * @brief Renders an entire scene.
 *
 * This function calculates the viewport and iterates through each pixel and
 * calculates the ray for each pixel based
 * cameras position and orientation. 
 * @param  scene A pointer to the t_scene struct containing info about the scene,
 * objects, camera, and other elements
 */
void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_viewport	viewport;

	y = 0;
	init_mlx(scene);
	viewport = calculate_viewport(scene);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculate_ray_and_draw(scene, viewport, y, x);
			x++;
		}
		display_render_progress((y * 100) / HEIGHT);
		y++;
	}
	display_render_progress(100);
}

/**
 * @brief Calculates the ray direction, origin and colour and then draws it to the mlx
 * window.
 * @param scene Contains info about the scene, camera and other elements.
 * @param viewport The viewport used to calculate the ray direction
 * @param y The current y pixel position
 * @param x The current x pixel position 
 */
t_colour	anti_aliasing(t_scene *scene, t_viewport vp, int x, int y);

static void	calculate_ray_and_draw(t_scene *scene, t_viewport viewport, int y, int x)
{
	t_colour	pixel_colour;

	pixel_colour = anti_aliasing(scene, viewport, x, y);
	mlx_put_pixel(scene->img, x, y, get_rgb(pixel_colour));
}

/**
 * @brief Calculates the viewport based on the camera FOV (stored in the scene `stuct`).
 * @param scene Pointer to the t_scene struct containing the camera and other
 * scene elements
 * @return A viewport struct containing all viewport information.
 */
static t_viewport	calculate_viewport(t_scene *scene)
{
	t_viewport	viewport;
	double		vp_height;
	double		vp_width;

	vp_height = 2.0 * tan((scene->camera.fov * (M_PI / 180.0)) / 2.0);
	vp_width = vp_height * ((double)WIDTH / (double)HEIGHT);
	assign_viewport_vectors(&viewport, scene, vp_height, vp_width);
	return (viewport);
}

/**
 * @brief Calculates and assigns data to the given `viewport` param.
 * This includes the camera direction, upper left corner and the pixel at (0,0).
 * @param viewport The variable to assign data to.
 * @param scene Contains scene related info.
 * @param vp_height The viewport height
 * @param vp_width The viewport width
 * @note This function is a helper function for `static t_viewport	calculate_viewport(t_scene *scene);`
 */
static void	assign_viewport_vectors(t_viewport *viewport, t_scene *scene, double vp_height, double vp_width)
{
	t_vector	backward;
	t_vector	pixel_delta_u;
	t_vector	pixel_delta_v;
	double		focal_length;

	focal_length = 1.0;
	viewport->camera_direction = normalize_vector(scene->camera.or_vect);
	viewport->camera_direction.x *= -1;
	viewport->camera_direction.y *= -1;
	viewport->camera_direction.z *= -1;
	viewport->horizontal = (t_vector){vp_width, 0, 0};
	viewport->vertical = (t_vector){0, -vp_height, 0};
	// Get lower upper corner
	backward = vec_multiply(viewport->camera_direction, to_vec(-focal_length));
	viewport->upper_left_corner = vec_add(scene->camera.cords, backward);
	viewport->upper_left_corner = vec_subtract(viewport->upper_left_corner, vec_divide(viewport->horizontal, (t_vector){2, 2, 2}));
	viewport->upper_left_corner = vec_subtract(viewport->upper_left_corner, vec_divide(viewport->vertical, (t_vector){2, 2, 2}));
	// Get first pixel (0,0) in viewport
	pixel_delta_u = vec_divide(viewport->horizontal, to_vec(WIDTH));
	pixel_delta_v = vec_divide(viewport->vertical, to_vec(HEIGHT));
	viewport->pixel00_loc = vec_multiply(vec_add(pixel_delta_u, pixel_delta_v), to_vec(0.5));
	viewport->pixel00_loc = vec_add(viewport->upper_left_corner, viewport->pixel00_loc);
}
