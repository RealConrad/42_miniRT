/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:00 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:01 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Checks if a ray intersects->hits an object
 * @param object the list of objects
 * @param ray the ray to check
 * @return the distance from the ray origin to the hit point, -1 for no hit
 */
double	hit_object(t_object *object, t_ray *ray)
{
	if (object->sphere != NULL)
		return (hit_sphere(object->sphere, ray), ray->distance);
	else if (object->cylinder != NULL)
		return (hit_cylinder(object->cylinder, ray), ray->distance);
	else if (object->plane != NULL)
		return (hit_plane(object->plane, ray), ray->distance);
	return (-1.0);
}
