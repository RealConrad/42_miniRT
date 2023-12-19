
#include "mini_rt.h"

static void	init_sphere(t_scene *scene, char **split, char *line, int fd);
static void	init_cylinder(t_scene *scene, char **split, char *line, int fd);

void	input_object(char *line, t_scene *scene, int fd, char **split)
{
	if (ft_strncmp(split[0], "sp", 3) == 0)
		init_sphere(scene, split, line, fd);
	if (ft_strncmp(split[0], "pl", 3) == 0)
		init_cylinder(scene, split, line, fd);
	if (ft_strncmp(split[0], "cy", 3) == 0)
		return ;
}

static void	init_cylinder(t_scene *scene, char **split, char *line, int fd)
{
	t_object	*object;
	int			i;

	i = 0;
	while (split[i])
		i++;
	if (i != 6 && i != 8 && i != 10 && i != 12)
		exit_analize(line, scene, fd, split);
	object = ft_calloc(1, sizeof(t_object));
	if (!object)
		exit_analize(line, scene, fd, split);
	object->cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!object->cylinder)
		exit_analize(line, scene, fd, split);
	if (!legal_vector_input(split, 1))
		exit_analize(line, scene, fd, split);
	object->cylinder->cords = get_vector_input(split, 1);
	if (ft_)

}

static void	init_sphere(t_scene *scene, char **split, char *line, int fd)
{
	t_object	*object;
	int			i;

	i = 0;
	while (split[i])
		i++;
	if (i != 4 && i != 6 && i != 8)
		exit_analize(line, scene, fd, split);
	object = ft_calloc(1, sizeof(t_object));
	if (!object)
		exit_analize(line, scene, fd, split);
	object->sphere = ft_calloc(1, sizeof(t_sphere));
	if (!object->sphere)
		exit_analize(line, scene, fd, split);
	if (!legal_vector_input(split, 1))
		exit_analize(line, scene, fd, split);
	object->sphere->cords = get_vector_input(split, 1);
	if (ft_strchr(split[1], ',') && atof_check(split[2]))
		object->sphere->diameter = atof(split[2]);
	else if (atof_check(split[4]))
		object->sphere->diameter = atof(split[4]);
	else
		exit_analize(line, scene, fd, split);
	if (ft_strchr(split[i - 1], ','))
		object->sphere->colour = get_colour_input(split, i - 3);
	else
		object->sphere->colour = get_colour_input(split, i - 1);
	if (!legal_colour(object->sphere->colour))
		exit_analize(line, scene, fd, split);
	add_object_to_linked_list(scene, object);
}

void	free_objects(t_object **objects)
{
	t_object	*next;
	t_object	*current;

	if (*objects == NULL)
		return ;
	current = *objects;
	next = current->next;
	while (current != NULL)
	{
		if (current->sphere != NULL)
			free(current->sphere);
		if (current->plane != NULL)
			free(current->plane);
		if (current->cylinder != NULL)
			free(current->cylinder);
		free(current);
		current = next;
		next = current->next;
	}
	*objects = NULL;
}


