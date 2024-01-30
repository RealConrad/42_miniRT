/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:33 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:35 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Initialises the window and puts the image to the window
 * @param scene Contains the mlx to initalize.
 */
void	init_mlx(t_scene *scene)
{
	scene->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (scene->mlx == NULL)
		exit_render(scene, "mlx_init failed");
	scene->img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (scene->img == NULL)
		exit_render(scene, "mlx_new_img failed");
	mlx_key_hook(scene->mlx, (void *)escape, NULL);
	mlx_close_hook(scene->mlx, (void *)close_win, NULL);
	mlx_image_to_window(scene->mlx, scene->img, 0, 0);
}

/**
 * @brief Cleanly exits the program during the rendering
 * @param scene the scene to free the objects
 * @param msg the error message to print
 */
void	exit_render(t_scene *scene, char *msg)
{
	free_objects(scene->objects);
	ft_fprintf(2, "Error\n");
	ft_fprintf(2, "%s\n", msg);
	exit(1);
}
