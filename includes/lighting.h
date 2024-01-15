
#ifndef LIGHTING_H
# define LIGHTING_H

# include "mini_rt.h"

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

t_colour	get_ambient_light(t_colour obj_colour, t_amb_light amb);

#endif /*LIGHTING_H*/