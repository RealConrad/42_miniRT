
#include "mini_rt.h"

static t_ray	get_light_ray(t_light light, t_vector hit_point);
static bool		light_hit(t_ray ray, t_object *objects, t_vector hit_point);

void	lighting(t_scene *scene, t_ray *ray)
{
	t_ray		light_ray;

	if (ray->distance < 0.0)
	{
		ray->ray_colour = get_ambient_light((t_colour){255, 255, 255}, scene->amb_light);
		return ;
	}
	light_ray = get_light_ray(scene->light, ray->hit_point);
	if (light_hit(light_ray, scene->objects, ray->hit_point) == true)
	{
		ray->ray_colour = (t_colour){255, 255, 0};
		return ;
	}
	ray->ray_colour = (t_colour){0, 0, 0};
}

static t_ray	get_light_ray(t_light light, t_vector hit_point)
{
	t_ray	light_ray;

	light_ray.origin = hit_point;
	light_ray.direction = vec_subtract(light.cords, hit_point);
	light_ray.direction = normalize_vector(light_ray.direction);
	light_ray.hit_point = light.cords;
	// if (hit_point.y > light.cords.y)
	// 	light_ray.direction.y *= -1;
	return (light_ray);
}

static bool	light_hit(t_ray ray, t_object *objects, t_vector hit_point)
{
	t_object	*temp;
	double		old_hit;
	double		distance;

	temp = objects;
	old_hit = 0;
	(void)hit_point;
	while (temp != NULL)
	{
		distance = hit_object(temp, &ray);
		if ((distance < old_hit || old_hit == 0) && distance > 0.0)
			old_hit = distance;
		temp = temp->next;
	}
	if (old_hit == 0)
		return (true);
	return (false);
}

/**
 * @brief Gets the ambient diffusion for the phong model (ka)
 * @param amb the ambient lighting
 * @param obj_coefficient the way the object diffuses light (between 0 and 1)
 * @return the ambient diffusion colour
 */
t_colour	get_ambient_diffusion(t_amb_light amb, double obj_coefficient)
{
	t_colour ambient;

	ambient.r = obj_coefficient * amb.light_ratio * amb.colour_in_range.r;
	ambient.g = obj_coefficient * amb.light_ratio * amb.colour_in_range.g;
	ambient.b = obj_coefficient * amb.light_ratio * amb.colour_in_range.b;
	return (ambient);
}

/**
 * @brief Gets the diffusion for the phong model (ka)
 * @param ray the ray from the camera
 * @param light the light source
 * @param obj_diff_co material's diffuse reflection coefficient (between 0 and 1)
 * @return the diffusion colour
 */
t_colour	get_diffuse(t_ray *ray, t_light light, double obj_diff_co)
{
	t_vector	hp_to_light;
	double		dot_diff;
	double		diffuse;
	t_colour	diff_colour;

	hp_to_light = vec_subtract(light.cords, ray->hit_point);
	hp_to_light = normalize_vector(hp_to_light);
	dot_diff = dot_product(ray->surface_norm, hp_to_light);

	diffuse = obj_diff_co * (light.light_ratio * fmax(dot_diff, 0));
	diff_colour.r = light.colour.r * diffuse;
	diff_colour.g = light.colour.g * diffuse;
	diff_colour.b = light.colour.b * diffuse;
	return (diff_colour);
}

t_vector reflect(t_vector incident, t_vector normal)
{
	double		d_product;
	t_vector	reflection;
	
	d_product = dot_product(incident, normal);
	d_product = d_product * 2;
	reflection = vec_subtract(incident, vec_scalar_multiply(normal, d_product));
	return (normalize_vector(reflection));
}

/**
 * @brief Gets the diffusion for the phong model (ka)
 * @param ray the ray from the camera
 * @param light the light source
 * @param obj_shiny material's shniniess (between 0 and 1)
 * @param obj_specular material's specular coefficient (between 0 and 1)
 * @return the diffusion colour
 */
t_colour	calculate_specular(t_ray *ray, t_light light, double obj_shiny, double obj_specular)
{
	t_vector	reflect_dir;
	double		dot_rv;
	double		spec_factor;
	t_colour	specular;

	reflect_dir = reflect(ray->direction, ray->surface_norm);
	dot_rv = dot_product(reflect_dir, ray->direction);
	spec_factor = fmax(dot_rv, 0);
	spec_factor = pow(spec_factor, obj_shiny);

	spec_factor = obj_specular * (light.light_ratio * spec_factor);
	specular.r = light.colour.r * spec_factor;
	specular.g = light.colour.g * spec_factor;
	specular.b = light.colour.b * spec_factor;
	return (specular);
}

// Helper function to clamp a value within a specified range
double	clamp(double value, double min, double max)
{
	return fmin(fmax(value, min), max);
}

// t_colour calculate_phong_reflection(t_ray *ray, t_light light, t_ambient_light amb_light)
// {
//     t_colour ambient = calculate_ambient(ray->object->material.ambient, amb_light.intensity);
//     t_colour diffuse = calculate_diffuse(ray, light);
//     t_colour specular = calculate_specular(ray, light);

//     // Add up the components
//     t_colour result;
//     result.r = ambient.r + diffuse.r + specular.r;
//     result.g = ambient.g + diffuse.g + specular.g;
//     result.b = ambient.b + diffuse.b + specular.b;

//     // Ensure color components are within the valid range (0-255)
//     result.r = clamp(result.r, 0, 255);
//     result.g = clamp(result.g, 0, 255);
//     result.b = clamp(result.b, 0, 255);

//     return result;
// }

/*
** 
** Ip​=ka​⋅Ia​+kd​⋅Id​⋅(N⋅L)+ks​⋅Is​⋅(R⋅V)n
** 
** ka​⋅Ia see get_ambient_diffusion
** 
** where:
** 
**     IpIp​ is the intensity of the reflected light.
**     kaka​, kdkd​, and ksks​ are the ambient, diffuse, and specular reflection coefficients, respectively.
**     IaIa​, IdId​, and IsIs​ are the intensities of the ambient, diffuse, and specular light, respectively.
**     NN is the normalized surface normal.
**     LL is the normalized direction vector from the hit point to the light source.
**     RR is the normalized reflection vector.
**     VV is the normalized direction vector from the hit point to the viewer.
**     nn is the shininess exponent.
*/