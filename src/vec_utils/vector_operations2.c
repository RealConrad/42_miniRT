/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:46:45 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:46:47 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Takes 2 vectors and returns a single scalar value. This works
 * by multiplying the 2 vectors elements.
 * @param v1 Vector 1
 * @param v2 Vector 2
 * @return the dot product
 * @throw if the dot product is bigger DOUBLE_MAX or smaller
 * DOUBLE min, it will overflow
 */
double	dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/**
 * @brief Converts the given double to a vector.
 *
 * The X,Y,Z elements of the vector will all be set to `n`.
 * @param n The double to be converted to a vector.
 * @return A newly created vector from `n`.
 */
t_vector	to_vec(double n)
{
	return ((t_vector){n, n, n});
}

/**
 * @brief Multiplies the vector by factor scalar
 * @param v the vector as product 1
 * @param scalar the scalar as product 2
 * @return the product of the vector and the scalar
 * @throw If the product is bigger DOUBLE_MAX or smaller
 * DOUBLE min, it will overflow
 */
t_vector	vec_scalar_multiply(t_vector v, double scalar)
{
	return ((t_vector){v.x * scalar, v.y * scalar, v.z * scalar});
}

/**
 * @brief Gets the length of a vector
 * @param v the vector
 * @return the length of the vector
 * @throw If the vector squared is bigger DOUBLE_MAX or smaller
 * DOUBLE min, it will overflow
 */
double	vec_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 * @brief Calculates the cross product of 2 vectors.
 * 
 * The cross productc is a vector that is perpendicular to both
 * given vectors and a magnitude/length equal to the area of
 * the parallelogram that the vectors spann.
 * @param v1 First vector
 * @param v2 Second vector 
 * @return The crosss product of v1 and v2
 */
t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;
	return (result);
}
