
#include "mini_rt.h"

static t_colour	blend_colour(t_colour pixel_colour, t_colour temp_colour);
// static t_vector	get_random_offset(t_vector horiz_scale, t_vector vert_scale);
static t_vector	get_pixel_center(t_viewport vp, int x, int y);

/**
 * @brief Sends multiple rays per pixel and averages the colour
 * @param scene the scene
 * @param vp the viewport
 * @param x the x coordinate of the pixel
 * @param y the y coordinate of the pixel
 * @return the colour of the pixel
 */
t_colour	anti_aliasing(t_scene *scene, int x, int y)
{
	int			i;
	int			j;
	double		result;
	t_colour	pixel_colour;
	t_ray		ray;

	i = 0;
	j = 0;
	pixel_colour = (t_colour){0, 0 , 0};
	while (i < RPP)
	{
		j = 0;
		while (j < RPP)
		{
			ray.ray_colour = (t_colour){0, 0, 0};
			ray.origin = scene->camera.cords;
			ray.direction = normalize_vector(vec_subtract(get_pixel_center(scene->viewport, x, y), scene->camera.cords));
			get_ray_intersection(&ray, scene->objects);
			ray.hit_point = vec_add(ray.hit_point, vec_scalar_multiply(ray.surface_norm, EPSILON));
			lighting2(scene, &ray);
			pixel_colour = blend_colour(pixel_colour, ray.ray_colour);
			j++;
		}
		i++;
	}
	result = 1 / (RPP * RPP);
	pixel_colour = colour_scalar_multiply(pixel_colour, result);
	// pixel_colour.r /= RPP;
	// pixel_colour.g /= RPP;
	// pixel_colour.b /= RPP;
	return (pixel_colour);
}

static t_vector	get_pixel_center(t_viewport vp, int x, int y)
{
	t_vector	pixel_center;

	pixel_center = vec_add(vp.pixel00_loc, vec_scalar_multiply(vp.delta_u, x));
	pixel_center = vec_add(pixel_center, vec_scalar_multiply(vp.delta_v, y));
	// pixel_center = vec_add(pixel_center, vec_scalar_multiply(vp.delta_u, 0.5));
	// pixel_center = vec_add(pixel_center, vec_scalar_multiply(vp.delta_v, 0.5));
	return (pixel_center);
}

/**
 * @brief Adds to colours together
 * @param pixel_colour 
 * @param temp_colour 
 * @return the colours added together
 * @note The new colour will potentially be bigger than 255
 * and needs to be divided by the amount of colours added
 * @throw Adding way too many colours will result in an integer overflow
 */
static t_colour	blend_colour(t_colour pixel_colour, t_colour temp_colour)
{
	t_colour	new_colour;

	new_colour.r = pixel_colour.r + temp_colour.r;
	new_colour.g = pixel_colour.g + temp_colour.g;
	new_colour.b = pixel_colour.b + temp_colour.b;
	return (new_colour);
}

// static t_vector	get_random_offset(t_vector horiz_scale, t_vector vert_scale)
// {
// 	t_vector	random_offset;
// 	t_vector	rand_1;
// 	t_vector	rand_2;
// 	t_vector	h_mult;
// 	t_vector	v_mult;

// 	rand_1 = to_vec(random_double());
// 	rand_2 = to_vec(random_double());
// 	h_mult = vec_multiply(horiz_scale, rand_1);
// 	v_mult = vec_multiply(vert_scale, rand_2);
// 	random_offset = vec_add(h_mult, v_mult);
// 	return (random_offset);
// }
