/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:46:18 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:46:20 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Gets a random double
 * @return Returns a double between -0.5 and 0.5
 * @note arc4random is used since AA isn't part of the mandatory
 */
double	random_double(void)
{
	return (((arc4random() / (double)UINT32_MAX) - 0.5));
}
