/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:38 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:40 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Calculates the point of intersection based on the distance
 * @param ray The given ray.
 * @param distance The distance from the rays origin along the ray.
 * @return The position vector of the point along the ray.
 */
t_vector	ray_at(t_ray ray, double distance)
{
	t_vector	result;

	result = vec_add(ray.origin, vec_scalar_multiply(
				normalize_vector(ray.direction), distance));
	return (result);
}

/**
 * @brief Determines if the given ray intersects with an object.
 * @param ray The ray to check for intersection
 * @param objects The list of objects in the scene.
 * @note If the ray distance is -1, there was no intersection.
 * If its a positive value, there was intersection.
 */
void	get_ray_intersection(t_ray *ray, t_object *objects)
{
	t_object	*temp;
	double		distance;
	t_object	*closest;
	double		old_hit;

	closest = NULL;
	temp = objects;
	old_hit = 0;
	ray->distance = -1;
	while (temp)
	{
		distance = hit_object(temp, ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
		{
			closest = temp;
			old_hit = distance;
		}
		temp = temp->next;
	}
	if (closest)
		hit_object(closest, ray);
}
