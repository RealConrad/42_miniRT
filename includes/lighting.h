
#ifndef LIGHTING_H
# define LIGHTING_H

# include "mini_rt.h"

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

t_colour	get_ambient_light(t_amb_light amb, t_colour object_colour);
void		lighting(t_scene *scene, t_ray *ray);
void		lighting2(t_scene *scene, t_ray *ray);

#endif /*LIGHTING_H*/