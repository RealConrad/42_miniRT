/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:36:52 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 15:37:46 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
t_viewport	calculate_viewport(t_scene *scene)
{
	t_viewport	viewport;
	t_vector	temp_vector;
	t_vector	camera_vector;

	temp_vector = (t_vector){1, 0, 0};
	viewport.focal_length = round(WIDTH
			/ (2.0 * tan((scene->camera.fov * (M_PI / 180.0)) / 2.0)));
	camera_vector = vec_scalar_multiply(normalize_vector(scene->camera.or_vect),
			viewport.focal_length);
	if (vec_length(cross_product(camera_vector, temp_vector)) == 0)
		temp_vector = (t_vector){0, 0, 1};
	viewport.delta_v = vec_scalar_multiply(normalize_vector(
				cross_product(temp_vector, camera_vector)), HEIGHT);
	viewport.delta_u = vec_scalar_multiply(normalize_vector(
				cross_product(camera_vector, viewport.delta_v)), WIDTH);
	viewport.pixel00_loc = vec_scalar_multiply(viewport.delta_u, -0.5);
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc,
			vec_scalar_multiply(viewport.delta_v, -0.5));
	viewport.pixel00_loc = vec_add(vec_add(viewport.pixel00_loc,
				camera_vector), scene->camera.cords);
	viewport.delta_v = normalize_vector(viewport.delta_v);
	viewport.delta_u = normalize_vector(viewport.delta_u);
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc, vec_scalar_multiply(
				vec_add(viewport.delta_u, viewport.delta_v), 0.5));
	return (viewport);
}
