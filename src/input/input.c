/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:44:13 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:44:14 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Exits the program on escape press
 * @param keycode 
 * @param param the scene to free
 * @note LEAKS FOR NOW
 */
void	escape(keys_t keycode, void *param)
{
	(void)param;
	if (keycode == MLX_KEY_ESCAPE)
		exit(0);
}

void	close_win(void)
{
	exit(0);
}
