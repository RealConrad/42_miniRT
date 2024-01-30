/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:44:22 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:44:23 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Applies the ambient ratio and colour range to the objet colour
 * @param obj_colour The object colour to modify
 * @param amb the ambient light features
 * @return the modified colour
 */
t_colour	get_ambient_light(t_colour obj_colour, t_amb_light amb)
{
	t_colour	ambient_lighting;

	ambient_lighting.r = obj_colour.r * (amb.colour_in_range.r / 255)
		* amb.light_ratio;
	ambient_lighting.g = obj_colour.g * (amb.colour_in_range.g / 255)
		* amb.light_ratio;
	ambient_lighting.b = obj_colour.b * (amb.colour_in_range.b / 255)
		* amb.light_ratio;
	return (ambient_lighting);
}
