
#include "mini_rt.h"

/**
 * @brief Prints all the values in a scene
 * @param scene 
 */
void	t_print_scene(t_scene scene)
{
	t_object	*current;

	current = scene.objects;
	printf("---Ambient Lightning---\n");
	printf("Lightning ratio :%f\n", scene.amb_light.light_ratio);
	t_print_colour(scene.amb_light.colour);
	printf("\n---Camera---\n");
	t_print_vector(scene.camera.cords);
	t_print_vector(scene.camera.or_vect);
	printf("FOV: %d\n", scene.camera.fov);
	printf("\n---Light---\n");
	t_print_vector(scene.light.cords);
	printf("Light brightness ration %f\n", scene.light.light_ratio);
	t_print_colour(scene.light.colour);
	while (current != NULL)
	{
		t_print_object(current);
		current = current->next;
	}
}

/**
 * @brief Prints the values of a colour vector
 * @param colour 
 */
void	t_print_colour(t_colour colour)
{
	printf("Colour: %d, %d, %d\n", colour.r, colour.g, colour.b);
}

/**
 * @brief Prints the values of a vector
 * @param vector 
 */
void	t_print_vector(t_vector vector)
{
	printf("Vector coordinates xyz: %f, %f, %f\n",
		vector.x, vector.y, vector.z);
}

/**
 * @brief Prints all the values of an object
 * @param object 
 */
void	t_print_object(t_object *object)
{
	if (object->sphere != NULL)
	{
		printf("\n---Sphere---\n");
		t_print_vector(object->sphere->cords);
		printf("Sphere diameter: %f\n", object->sphere->diameter);
		t_print_colour(object->sphere->colour);
	}
	else if (object->plane != NULL)
	{
		printf("\n---Plane---\n");
		t_print_vector(object->plane->cords);
		t_print_vector(object->plane->threed_vec);
		t_print_colour(object->plane->colour);
	}
	else if (object->cylinder != NULL)
	{
		printf("\n---Cylinder---\n");
		t_print_vector(object->cylinder->cords);
		t_print_vector(object->cylinder->axis);
		printf("Cylinder diameter: %f\n", object->cylinder->diameter);
		printf("Cylinder height: %f\n", object->cylinder->height);
		t_print_colour(object->cylinder->colour);
	}
}
