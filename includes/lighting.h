
#ifndef LIGHTING_H
# define LIGHTING_H

# include "mini_rt.h"

# define SHINY 100

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

t_colour	get_ambient_light(t_colour obj_colour, t_amb_light amb);
void		lighting(t_scene *scene, t_ray *ray);
void		lighting2(t_scene *scene, t_ray *ray);
t_colour	add_phong_elements(t_colour a, t_colour d, t_colour s);

#endif /*LIGHTING_H*/