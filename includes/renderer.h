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

double		hit_object(t_object *object, t_ray ray);
t_vector	ray_at(t_ray ray, double t);

#endif /*RENDERER_H*/