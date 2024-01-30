/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dabs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:56 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:57 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Gets the absolute value of a double
 * @param nb the double to get the absolute of
 * @return the absolute value of nb
 * @throw the minumum double value returns itself
 */
double	ft_dabs(double nb)
{
	if (nb >= 0)
		return (nb);
	else if (nb == 2.2250738585072014e-308)
		return (nb);
	else
		return (-nb);
}
