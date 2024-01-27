
#include "mini_rt.h"

/**
 * @brief Calculates the viewport based on the camera FOV
 * (stored in the scene `stuct`).
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
	viewport.focal_length = round(WIDTH / (2.0 * tan((scene->camera.fov * (M_PI / 180.0)) / 2.0)));
	camera_vector = vec_scalar_multiply(normalize_vector(scene->camera.or_vect), viewport.focal_length);
	if (vec_length(cross_product(camera_vector, temp_vector)) == 0)
		temp_vector = (t_vector){0, 0, 1};

	// Get delta
	viewport.delta_v = vec_scalar_multiply(normalize_vector(cross_product(temp_vector, camera_vector)), HEIGHT);
	viewport.delta_u = vec_scalar_multiply(normalize_vector(cross_product(viewport.delta_v, camera_vector)), -WIDTH);

	// Get upper left corner
	viewport.pixel00_loc = vec_scalar_multiply(viewport.delta_u, -0.5);
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc, vec_scalar_multiply(viewport.delta_v, -0.5));
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc, camera_vector);
	viewport.pixel00_loc = vec_subtract(viewport.pixel00_loc, scene->camera.cords);
	viewport.delta_v = normalize_vector(viewport.delta_v);
	viewport.delta_u = normalize_vector(viewport.delta_u);
	viewport.pixel00_loc = vec_add(viewport.pixel00_loc, vec_scalar_multiply(vec_add(viewport.delta_u, viewport.delta_v), 0.5));

	return (viewport);
}

/**
 * @brief Calculates and assigns data to the given `viewport` param.
 * This includes the camera direction, upper left corner and the pixel at (0,0).
 * @param viewport The variable to assign data to.
 * @param scene Contains scene related info.
 * @param vp_height The viewport height
 * @param vp_width The viewport width
 * @note This function is a helper function for
 * `static t_viewport	calculate_viewport(t_scene *scene);`
 */
// void	assign_viewport_vectors(t_viewport *viewport, t_scene *scene, double cam_focal)
// {

// 	(void)viewport;
// 	(void)scene;
// 	(void)cam_focal;
// 	// t_vector	backward;
// 	// t_vector	pixel_delta_u;
// 	// t_vector	pixel_delta_v;
// 	// double		focal_length;

// 	// focal_length = 1.0;
// 	// viewport->camera_direction = normalize_vector(scene->camera.or_vect);
// 	// viewport->camera_direction.x *= -1;
// 	// viewport->camera_direction.y *= -1;
// 	// viewport->camera_direction.z *= -1;
// 	// viewport->horizontal = (t_vector){vp_width, 0, 0};
// 	// viewport->vertical = (t_vector){0, -vp_height, 0};
// 	// backward = vec_multiply(viewport->camera_direction, to_vec(-focal_length));
// 	// viewport->upper_left_corner = vec_add(scene->camera.cords, backward);
// 	// viewport->upper_left_corner = vec_subtract(viewport->upper_left_corner,
// 	// 		vec_divide(viewport->horizontal, (t_vector){2, 2, 2}));
// 	// viewport->upper_left_corner = vec_subtract(viewport->upper_left_corner,
// 	// 		vec_divide(viewport->vertical, (t_vector){2, 2, 2}));
// 	// pixel_delta_u = vec_divide(viewport->horizontal, to_vec(WIDTH));
// 	// pixel_delta_v = vec_divide(viewport->vertical, to_vec(HEIGHT));
// 	// viewport->pixel00_loc = vec_multiply(vec_add(pixel_delta_u, pixel_delta_v),
// 	// 		to_vec(0.5));
// 	// viewport->pixel00_loc = vec_add(viewport->upper_left_corner,
// 	// 		viewport->pixel00_loc);
// }
