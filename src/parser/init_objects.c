/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:28:28 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:47:21 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void		add_object_to_linked_list(t_scene *scene, t_object *object);
static t_object	*common_init_object(char **tokens, t_object_type type);

/**
 * @brief Initializes a plane object and adds to the linked list
 * contained in `scene`.
 * @param scene The struct that holds all data regarding the scene
 * @param tokens An array of strings that contain the plane data.
 * @param fd The file desciptor of the scene file.
 */
void	init_plane(t_scene *scene, char **tokens, int fd)
{
	t_object	*object;

	object = common_init_object(tokens, PLANE);
	if (!object)
		exit_analyse(scene, tokens, fd, object);
	assign_vector(&(object->plane->cords), tokens, 1);
	assign_vector(&(object->plane->threed_vec), tokens, 4);
	assign_colour(&(object->plane->colour), tokens, 7);
	if (!legal_vector(object->plane->threed_vec, -1, 1)
		|| !legal_colour(object->plane->colour))
		exit_analyse(scene, tokens, fd, object);
	add_object_to_linked_list(scene, object);
}

/**
 * @brief Initializes a sphere object and adds to the linked list
 * contained in `scene`.
 * @param scene The struct that holds all data regarding the scene
 * @param tokens An array of strings that contain the sphere data.
 * @param fd The file desciptor of the scene file.
 */
void	init_sphere(t_scene *scene, char **tokens, int fd)
{
	t_object	*object;

	object = common_init_object(tokens, SPHERE);
	if (!object)
		exit_analyse(scene, tokens, fd, object);
	assign_vector(&(object->sphere->cords), tokens, 1);
	object->sphere->diameter = ft_atof(tokens[4]);
	assign_colour(&(object->sphere->colour), tokens, 5);
	if (!legal_colour(object->sphere->colour))
		exit_analyse(scene, tokens, fd, object);
	add_object_to_linked_list(scene, object);
}

/**
 * @brief Initializes a cylinder object and adds to the linked list
 * contained in `scene`.
 * @param scene The struct that holds all data regarding the scene
 * @param tokens An array of strings that contain the cylinder data.
 * @param fd The file desciptor of the scene file.
 */
void	init_cylinder(t_scene *scene, char **tokens, int fd)
{
	t_object	*object;

	object = common_init_object(tokens, CYLINDER);
	if (!object)
		exit_analyse(scene, tokens, fd, object);
	assign_vector(&(object->cylinder->cords), tokens, 1);
	assign_vector(&(object->cylinder->axis), tokens, 4);
	object->cylinder->diameter = ft_atof(tokens[7]);
	object->cylinder->height = ft_atof(tokens[8]);
	assign_colour(&(object->cylinder->colour), tokens, 9);
	if (!legal_colour(object->cylinder->colour)
		|| !legal_vector(object->cylinder->axis, -1, 1))
		exit_analyse(scene, tokens, fd, object);
	add_object_to_linked_list(scene, object);
}

/**
 * @brief Adds the given `object` to the end of the linked list.
 * @param scene Struct that holds all the scene objects.
 * @param object The object to add to the linked list.
 */
static void	add_object_to_linked_list(t_scene *scene, t_object *object)
{
	t_object	*temp;

	object->next = NULL;
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

/**
 * @brief Allocates memory for the given object and does malloc checks.
 * It also checks if the given tokens are valid.
 * @param tokens The tokens to check if are valid or not.
 * @param type The type of object to allocate memory for.
 * @return A newly allocated `t_object` or NULL if allocation fails or if
 * tokens are invalid.
 */
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
