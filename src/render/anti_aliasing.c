/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_aliasing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:29 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:31 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_colour	blend_colour(t_colour pixel_colour, t_colour temp_colour);
static t_vector	get_pixel_center(t_viewport vp, int x, int y);
static t_vector	get_random_offset(void);

t_colour	anti_aliasing(t_scene *scene, int x, int y)
{
	int			i;
	t_colour	pixel_colour;
	t_ray		ray;

	i = 0;
	pixel_colour = (t_colour){0, 0, 0};
	while (i < RPP)
	{
		ray.ray_colour = (t_colour){0, 0, 0};
		ray.origin = scene->camera.cords;
		ray.direction = get_pixel_center(scene->viewport, x, y);
		ray.direction = vec_subtract(ray.direction, scene->camera.cords);
		ray.direction = normalize_vector(ray.direction);
		get_ray_intersection(&ray, scene->objects);
		ray.hit_point = vec_add(ray.hit_point,
				vec_scalar_multiply(ray.surface_norm, EPSILON));
		lighting(scene, &ray);
		pixel_colour = blend_colour(pixel_colour, ray.ray_colour);
		i++;
	}
	pixel_colour.r /= RPP;
	pixel_colour.g /= RPP;
	pixel_colour.b /= RPP;
	return (pixel_colour);
}

/**
 * @brief Calculates the pixel center based on the current x and y position.
 * 
 * Scales the deltaU by x and deltaV by y.
 * @param vp The viewport containing the deltaU and deltaV.
 * @param x The current x position in the scene/widnow.
 * @param y The current y position in the scene/window.
 * @return The pixel center for the given x/y position.
 */
static t_vector	get_pixel_center(t_viewport vp, int x, int y)
{
	t_vector	pixel_center;
	t_vector	scaled_detla_u;
	t_vector	scaled_detla_v;

	scaled_detla_u = vec_scalar_multiply(vp.delta_u, x);
	scaled_detla_v = vec_scalar_multiply(vp.delta_v, y);
	pixel_center = vec_add(vp.pixel00_loc, scaled_detla_u);
	pixel_center = vec_add(pixel_center, scaled_detla_v);
	pixel_center = vec_add(pixel_center, get_random_offset());
	return (pixel_center);
}

/**
 * @brief Adds 2 colours together
 * @param c1 The first colour
 * @param c2 The second colour
 * @return A new colour that is the result from addding `c1` and `c2`
 */
static t_colour	blend_colour(t_colour c1, t_colour c2)
{
	t_colour	new_colour;

	new_colour.r = c1.r + c2.r;
	new_colour.g = c1.g + c2.g;
	new_colour.b = c1.b + c2.b;
	return (new_colour);
}

static t_vector	get_random_offset(void)
{
	t_vector	random_offset;

	random_offset.x = random_double();
	random_offset.y = random_double();
	random_offset.z = random_double();
	return (random_offset);
}
