/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:39:09 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:39:11 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "mini_rt.h"

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

t_vector	vec_add(t_vector v1, t_vector v2);
t_vector	vec_subtract(t_vector v1, t_vector v2);
t_vector	vec_divide(t_vector v1, t_vector v2);
t_vector	vec_multiply(t_vector v1, t_vector v2);
t_vector	normalize_vector(t_vector v);
double		dot_product(t_vector v1, t_vector v2);
t_vector	to_vec(double n);
t_vector	vec_scalar_multiply(t_vector v, double scalar);
double		vec_length(t_vector v);
t_vector	cross_product(t_vector a, t_vector b);

#endif /*VECTOR_H*/