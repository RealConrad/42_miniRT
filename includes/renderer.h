
#ifndef RENDERER_H
# define RENDERER_H

# include <stdint.h>
# include "struct.h"

void		render_scene(t_scene *scene);
void		render_cylinder(t_scene *scene, t_cylinder *cylinder);
void		render_plane(t_scene *scene, t_plane *plane);
void		render_sphere(t_scene *scene, t_sphere *sphere);
uint32_t	get_rgb(t_colour colour);
bool		get_ray_intersection(t_ray *ray, t_object *objects);
t_vector	ray_at(t_ray ray, double t);
t_colour	anti_aliasing(t_scene *scene, t_viewport vp, int x, int y);

/* --------------------------------- Objects -------------------------------- */

double		hit_object(t_object *object, t_ray *ray);
void		hit_plane(t_plane *plane, t_ray *ray);
void		hit_sphere(t_sphere *sphere, t_ray *ray);
void		hit_cylinder(t_cylinder *cylinder, t_ray *ray);
double		find_closest_cap(t_cy_data *data);
t_vector	get_cylinder_surface_norm(t_cy_data data, t_ray *ray,
				t_cylinder *cylinder);
t_vector	get_cylinder_surface_norm(t_cy_data data, t_ray *ray, t_cylinder *cylinder);

/* ----------------------------------- MLX ---------------------------------- */

void		init_mlx(t_scene *scene);
void		exit_render(t_scene *scene, char *msg);

/* -------------------------------- Viewport -------------------------------- */

t_viewport	calculate_viewport(t_scene *scene);
void		assign_viewport_vectors(t_viewport *viewport, t_scene *scene,
				double vp_height, double vp_width);

#endif /*RENDERER_H*/