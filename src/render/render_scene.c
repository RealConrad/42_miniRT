/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:45:43 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:45:45 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	*render_rows(void *param);
static void	join_all(t_scene *scene, t_threads *thread);
static void	free_threads(t_scene *scene, t_threads *thread, int id);
static void	launch_threads(t_threads *thread, t_scene *scene);

/**
 * @brief Renders an entire scene.
 *
 * This function calculates the viewport and iterates through each pixel and
 * calculates the ray for each pixel based cameras position and orientation. 
 * @param  scene A pointer to the t_scene struct containing info about the scene,
 * objects, camera, and other elements
 */
void	render_scene(t_scene *scene)
{
	t_threads	*thread;
	int			i;

	i = 0;
	thread = ft_calloc(scene->core_num, sizeof(t_threads));
	if (thread == NULL)
		free_threads(scene, thread, 1);
	init_mlx(scene);
	scene->viewport = calculate_viewport(scene);
	if (pthread_mutex_init(&(scene->mlx_lock), NULL) != 0)
		free_threads(scene, thread, 2);
	while (i < scene->core_num)
	{
		thread[i].scene = scene;
		i++;
	}
	launch_threads(thread, scene);
	join_all(scene, thread);
	free_threads(scene, thread, 0);
	display_render_progress(100);
}

static void	launch_threads(t_threads *thread, t_scene *scene)
{
	int			i;
	int			height_per_thread;

	i = 0;
	height_per_thread = HEIGHT / scene->core_num;
	while (i < scene->core_num)
	{
		thread[i].start_y = i * height_per_thread;
		thread[i].end_y = (i + 1) * height_per_thread;
		if (i == scene->core_num - 1)
			thread[i].end_y = HEIGHT;
		if (pthread_create(&(thread[i].t_id), NULL,
				render_rows, &(thread[i])) != 0)
			free_threads(scene, thread, 3);
		i++;
	}
}

static void	*render_rows(void *param)
{
	t_threads	*threads;
	int			y;
	int			x;
	t_colour	pixel_colour;
	int			end_y;

	threads = (t_threads *)param;
	y = threads->start_y;
	end_y = threads->end_y;
	while (y < end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_colour = anti_aliasing(threads->scene, x, y);
			pixel_colour = colour_scalar_multiply(pixel_colour, 255);
			pthread_mutex_lock(&(threads->scene->mlx_lock));
			mlx_put_pixel(threads->scene->img, x, y, get_rgb(pixel_colour));
			pthread_mutex_unlock(&(threads->scene->mlx_lock));
			x++;
		}
		y++;
	}
	return (0);
}

static void	join_all(t_scene *scene, t_threads *thread)
{
	int	i;

	i = 0;
	while (i < scene->core_num)
	{
		pthread_join(thread[i].t_id, NULL);
		i++;
	}
}

static void	free_threads(t_scene *scene, t_threads *thread, int id)
{
	if (thread != NULL)
		free(thread);
	pthread_mutex_destroy(&(scene->mlx_lock));
	free_objects(scene->objects);
	if (id == 1)
	{
		ft_fprintf(2, "Malloc fail in render\n");
		exit(1);
	}
	if (id == 2)
	{
		ft_fprintf(2, "Mutex init fail\n");
		exit(1);
	}
	if (id == 3)
	{
		ft_fprintf(2, "Pthread_create fail\n");
		exit(1);
	}
}
