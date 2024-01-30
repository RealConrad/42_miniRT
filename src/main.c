/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:46:25 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:46:27 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	check_no_light(t_scene *scene);
static void	exit_main(t_scene *scene, int msg);
static void	get_cores(t_scene *scene);

// void	leak_check(void)
// {
// 	system("leaks miniRT");
// }

int	main(int argc, char *argv[])
{
	t_scene		scene;

	if (argc != 2)
		parser_exit(INPUT_MISSING, NULL);
	if (ft_strncmp(argv[1] + (ft_strlen(argv[1]) - 3), ".rt", 4) != 0)
		parser_exit(INPUT_FILE, NULL);
	scene = (t_scene){};
	scene = parser(argv);
	check_no_light(&scene);
	get_cores(&scene);
	render_scene(&scene);
	mlx_loop(scene.mlx);
	return (0);
}

static void	check_no_light(t_scene *scene)
{
	if (!legal_colour(scene->light.colour))
		exit_main(scene, MISSING);
	if (scene->light.light_ratio == -1)
		exit_main(scene, MISSING);
	if (scene->amb_light.light_ratio == -1)
		exit_main(scene, MISSING);
	if (!legal_colour(scene->amb_light.colour_in_range))
		exit_main(scene, MISSING);
	if (scene->camera.or_vect.x == 0.0 && scene->camera.or_vect.y == 0.0
		&& scene->camera.or_vect.z == 0.0)
		exit_main(scene, FORMAT);
}

// atexit(leak_check);

static void	exit_main(t_scene *scene, int msg)
{
	free_objects(scene->objects);
	parser_exit(msg, NULL);
}

static void	get_cores(t_scene *scene)
{
	scene->core_num = sysconf(_SC_NPROCESSORS_ONLN);
	if (scene->core_num < 1)
		scene->core_num = 1;
	if (scene->core_num > 64)
		scene->core_num = 64;
}
