
#include "mini_rt.h"

void	hit_plane(t_plane *plane, t_ray *ray)
{
	double	d_pro;
	double	distance;

	d_pro = dot_product(plane->threed_vec, ray->direction);
	if (ft_dabs(d_pro) < EPSILON)
	{
		ray->distance = -1;
		return ;
	}
	distance = dot_product(vec_subtract(plane->cords, ray->origin),
			plane->threed_vec) / d_pro;
	if (distance < 0)
	{
		ray->distance = -1;
		return ;
	}
	ray->distance = distance;
	ray->ray_colour = plane->colour;
	ray->hit_point = ray_at(*ray, ray->distance);
}
