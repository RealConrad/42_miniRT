#include "mini_rt.h"

static void			calculate_ray_and_draw(t_scene *scene, int y, int x);
static t_viewport	calculate_viewport(t_scene *scene);

/**
 * @brief Renders an entire scene.
 *
 * This function calculates the viewport and iterates through each pixel and
 * calculates the ray for each pixel based cameras position and orientation. 
 * @param  scene A pointer to the t_scene struct containing info about the scene,
 * objects, camera, and other elements
 */
void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_colour	pixel_colour;

	y = 0;
	init_mlx(scene);
	scene->viewport = calculate_viewport(scene);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_colour = anti_aliasing(scene, x, y);
			pixel_colour = colour_scalar_multiply(pixel_colour, 255);
			mlx_put_pixel(scene->img, x, y, get_rgb(pixel_colour));
			x++;
		}
		display_render_progress((y * 100) / HEIGHT);
		y++;
	}
	display_render_progress(100);
}

/**
 * @brief Calculates the viewport based on the camera FOV.
 * 
 * It uses the camera's FOV to determine the scene's width and height to get
 * focal length. It also calculates the upper left pixel as well as the deltaV
 * and deltaU.
 * @param scene Pointer to the t_scene struct containing the camera and other
 * scene elements
 * @return A viewport struct containing all viewport information.
 */
static t_viewport	calculate_viewport(t_scene *scene)
{
	t_viewport	viewport;
	t_vector	temp_vector;
	t_vector	camera_vector;

	temp_vector = (t_vector){1, 0, 0};
	viewport.focal_length = round(WIDTH / (2.0 * tan((scene->camera.fov * (M_PI / 180.0)) / 2.0)));
	camera_vector = vec_scalar_multiply(normalize_vector(scene->camera.or_vect), viewport.focal_length);
	if (vec_length(cross_product(camera_vector, temp_vector)) == 0)
		temp_vector = (t_vector){0, 0, 1};
	viewport.delta_v = vec_scalar_multiply(normalize_vector(cross_product(temp_vector, camera_vector)), HEIGHT);
	viewport.delta_u = vec_scalar_multiply(normalize_vector(cross_product(camera_vector, viewport.delta_v)), WIDTH);
	viewport.pixel00_loc = vec_scalar_multiply(viewport.delta_u, -0.5);
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc, vec_scalar_multiply(viewport.delta_v, -0.5));
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc, camera_vector);
	viewport.pixel00_loc = vec_subtract(viewport.pixel00_loc, scene->camera.cords);
	viewport.delta_v = normalize_vector(viewport.delta_v);
	viewport.delta_u = normalize_vector(viewport.delta_u);
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc, vec_scalar_multiply(vec_add(viewport.delta_u, viewport.delta_v), 0.5));
	return (viewport);
}
