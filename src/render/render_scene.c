#include "mini_rt.h"

static void			calculate_ray_and_draw(t_scene *scene, int y, int x);

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

	y = 0;
	init_mlx(scene);
	scene->viewport = calculate_viewport(scene);
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculate_ray_and_draw(scene, y, x);
			x++;
		}
		display_render_progress((y * 100) / HEIGHT);
		y++;
	}
	display_render_progress(100);
}

/**
 * @brief Calculates the ray direction, origin and colour and then
 * draws it to the mlx window.
 * @param scene Contains info about the scene, camera and other elements.
 * @param viewport The viewport used to calculate the ray direction
 * @param y The current y pixel position
 * @param x The current x pixel position 
 */
static void	calculate_ray_and_draw(t_scene *scene, int y, int x)
{
	t_colour	pixel_colour;

	pixel_colour = anti_aliasing(scene, x, y);
	pixel_colour = colour_scalar_multiply(pixel_colour, 255);
	mlx_put_pixel(scene->img, x, y, get_rgb(pixel_colour));
}
