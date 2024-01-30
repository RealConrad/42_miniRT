/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:38:12 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:38:14 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "mini_rt.h"

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

t_colour	get_ambient_light(t_colour obj_colour, t_amb_light amb);
void		lighting(t_scene *scene, t_ray *ray);
t_colour	add_phong_elements(t_colour a, t_colour d, t_colour s);

#endif /*LIGHTING_H*/