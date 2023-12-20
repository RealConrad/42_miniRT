#include "mini_rt.h"

static void	add_object_to_linked_list(t_scene *scene, t_object *object);
static t_object	*common_init_object(char **tokens, t_object_type type);

void	init_plane(t_scene *scene, char **tokens, int fd)
{
	t_object	*object;

	object = common_init_object(tokens, PLANE);
	if (!object)
		exit_analize(scene, tokens, fd, object);
	assign_vector(&(object->plane->cords), tokens, 1);
	assign_vector(&(object->plane->threed_vec), tokens, 4);
	assign_colour(&(object->plane->colour), tokens, 7);
	if (!legal_vector(object->plane->threed_vec, -1, 1)
		|| !legal_colour(object->plane->colour))
		exit_analize(scene, tokens, fd, object);
	add_object_to_linked_list(scene, object);
}

void	init_sphere(t_scene *scene, char **tokens, int fd)
{
	t_object	*object;

	object = common_init_object(tokens, SPHERE);
	if (!object)
		exit_analize(scene, tokens, fd, object);
	assign_vector(&(object->sphere->cords), tokens, 1);
	object->sphere->diameter = ft_atof(tokens[4]);
	assign_colour(&(object->sphere->colour), tokens, 5);
	if (!legal_colour(object->sphere->colour))
		exit_analize(scene, tokens, fd, object);
	add_object_to_linked_list(scene, object);
}

void	init_cylinder(t_scene *scene, char **tokens, int fd)
{
	t_object	*object;

	object = common_init_object(tokens, CYLINDER);
	if (!object)
		exit_analize(scene, tokens, fd, object);
	assign_vector(&(object->cylinder->cords), tokens, 1);
	assign_vector(&(object->cylinder->axis), tokens, 4);
	object->cylinder->diameter = ft_atof(tokens[7]);
	object->cylinder->height = ft_atof(tokens[8]);
	assign_colour(&(object->cylinder->colour), tokens, 9);
	if (!legal_colour(object->cylinder->colour) || ! legal_vector(object->cylinder->axis, -1, 1))
		exit_analize(scene, tokens, fd, object);
	add_object_to_linked_list(scene, object);
}

static void	add_object_to_linked_list(t_scene *scene, t_object *object)
{
	t_object	*temp;

	if (!scene->objects)
		scene->objects = object;
	else
	{
		temp = scene->objects;
		while (temp->next)
			temp = temp->next;
		temp->next = object;
	}
}

static t_object	*common_init_object(char **tokens, t_object_type type)
{
	t_object	*object;

	if (!is_valid_numbers(tokens))
		return (NULL);
	object = ft_calloc(1, sizeof(t_object));
	if (!object)
		return (NULL);

	if (type == SPHERE)
		object->sphere = ft_calloc(1, sizeof(t_sphere));
	else if (type == CYLINDER)
		object->cylinder = ft_calloc(1, sizeof(t_cylinder));
	else if (type == PLANE)
		object->plane = ft_calloc(1, sizeof(t_plane));
	return (object);
}
