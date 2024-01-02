#ifndef RENDERER_H
# define RENDERER_H

# include <stdint.h>
# include "struct.h"

void		render_scene(t_scene *scene);
void		render_cylinder(t_scene *scene, t_cylinder *cylinder);
void		render_plane(t_scene *scene, t_plane *plane);
void		render_sphere(t_scene *scene, t_sphere *sphere);
uint32_t	get_rgb(t_colour colour);
t_colour	get_ray_colour(t_ray ray, t_object *objects);
t_colour	get_object_colour(t_object *object);

bool	check_object_intersection(t_object *object, t_ray ray);


t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_subtract(t_vector v1, t_vector v2);
t_vector	vec_divide(t_vector v1, t_vector v2);
t_vector	vec_multiply(t_vector v1, t_vector v2);
t_vector	normalize_vector(t_vector v);

#endif 