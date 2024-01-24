
#include "mini_rt.h"

static t_ray	get_light_ray(t_light light, t_vector hit_point);
static bool		light_hit(t_ray ray, t_object *objects);

static t_colour calc_phong_reflection(t_ray *ray, t_light light, t_amb_light amb_light);
static t_colour	get_ambient_diffusion(t_amb_light amb, double obj_coefficient);
static t_colour	calc_specular(t_ray *ray, t_light light, double obj_shiny, double obj_specular);
static t_colour	calc_diffuse(t_ray *ray, t_light light, double obj_diff_co);
static t_colour mix_colours(t_colour colour1, t_colour colour2, double intensity);

void	lighting(t_scene *scene, t_ray *ray)
{
	t_ray		light_ray;
	t_colour	amb;

	if (ray->distance < 0.0)
		ray->ray_colour = get_ambient_light(scene->amb_light, (t_colour){255, 255, 255});
	else
	{
		light_ray = get_light_ray(scene->light, ray->hit_point);
		if (light_hit(light_ray, scene->objects))
			ray->ray_colour = calc_phong_reflection(ray, scene->light, scene->amb_light);
		else
		{
			amb = get_ambient_diffusion(scene->amb_light, 0.4);
			ray->ray_colour = mix_colours(calc_phong_reflection(ray, scene->light, scene->amb_light), amb, 0.5);
		}
	}
}

static t_colour mix_colours(t_colour colour1, t_colour colour2, double intensity)
{
	t_colour	mixed;

	mixed.r = (1 - intensity) * colour1.r + intensity * colour2.r;
	mixed.g = (1 - intensity) * colour1.g + intensity * colour2.g;
	mixed.b = (1 - intensity) * colour1.b + intensity * colour2.b;
	return (mixed);
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

static bool	light_hit(t_ray ray, t_object *objects)
{
	t_object	*temp;
	double		old_hit;
	double		distance;

	temp = objects;
	old_hit = 0;
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
static t_colour	get_ambient_diffusion(t_amb_light amb, double obj_coefficient)
{
	t_colour ambient;

	ambient.r = obj_coefficient * amb.light_ratio * amb.colour.r;
	ambient.g = obj_coefficient * amb.light_ratio * amb.colour.g;
	ambient.b = obj_coefficient * amb.light_ratio * amb.colour.b;
	return (ambient);
}

/**
 * @brief Gets the diffusion for the phong model (ka)
 * @param ray the ray from the camera
 * @param light the light source
 * @param obj_diff_co material's diffuse reflection coefficient (between 0 and 1)
 * @return the diffusion colour
 */
static t_colour	calc_diffuse(t_ray *ray, t_light light, double obj_diff_co)
{
	t_colour	diff_colour;
	t_vector	hp_to_light;
	// double		dot_diff;
	// double		diffuse;

	hp_to_light = vec_subtract(light.cords, ray->hit_point);
	hp_to_light = normalize_vector(hp_to_light);
	double	dotLN = dot_product(hp_to_light, ray->surface_norm);
	dotLN = clamp(dotLN, 0.0, 1.0);
	diff_colour.r = obj_diff_co * dotLN * ray->ray_colour.r;
	diff_colour.g = obj_diff_co * dotLN * ray->ray_colour.g;
	diff_colour.b = obj_diff_co * dotLN * ray->ray_colour.b;
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
static t_colour	calc_specular(t_ray *ray, t_light light, double obj_shiny, double obj_specular)
{
	t_colour	specular;
	t_vector	hp_to_light;
	t_vector	ref;
	double		dotRV;

	hp_to_light = vec_subtract(light.cords, ray->hit_point);
	hp_to_light = normalize_vector(hp_to_light);
	ref = reflect(hp_to_light, ray->surface_norm);
	dotRV = dot_product(ref, vec_scalar_multiply(ray->direction, -1.0));
	dotRV = clamp(dotRV, 0., 1.);
	specular.r = obj_shiny * pow(dotRV, obj_specular) * light.colour.r;
	specular.g = obj_shiny * pow(dotRV, obj_specular) * light.colour.g;
	specular.b = obj_shiny * pow(dotRV, obj_specular) * light.colour.b;
	return (specular);
}


static t_colour calc_phong_reflection(t_ray *ray, t_light light, t_amb_light amb_light)
{
	t_colour	ambient;
	t_colour	diffuse;
	t_colour	specular;
	t_colour	result;

	ambient = get_ambient_diffusion(amb_light, 0.6);
	diffuse = calc_diffuse(ray, light, 0.5);
	specular = calc_specular(ray, light, 0.8, 10.0);

	// ambient.r = ambient.r / 3;
	// ambient.g = ambient.g / 3;
	// ambient.b = ambient.b / 3;
	// diffuse.r = diffuse.r / 3;
	// diffuse.g = diffuse.g / 3;
	// diffuse.b = diffuse.b / 3;
	// specular.r = specular.r / 3;
	// specular.g = specular.g / 3;
	// specular.b = specular.b / 3;

	result.r = ambient.r + diffuse.r + specular.r;
	result.g = ambient.g + diffuse.g + specular.g;
	result.b = ambient.b + diffuse.b + specular.b;

	result.r = clamp(result.r, 0, 255);
	result.g = clamp(result.g, 0, 255);
	result.b = clamp(result.b, 0, 255);
	return (result);
}

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

/*
** Phong Reflection:
** L = Ambient_Light + Diffusion + Specular
** 
** Ambient Light:
** L = Colour (object colour) * Amb_light_factor
** 
** Difusion:
** dotLN = dot(norm(light_pos - hit_point), surfaceNormal(hit_point))
** light_colour = light_colour * light_ratio(if this doesnt look good, try obj col)
** L = Diffusion_factor (0, 1) * dotLN * light_colour
** 
** Specular:
** vec3 R = reflect(norm(light_pos - hit_point), surface_normal);
** vec  V = direction_to_cam (reversed ray direction);
**      dotRV = dot(R, V);
** float alpha = 10.;
** L = Spec_factor(0, 1) * pow(dotRV, alpha) * colour_of_choice(light colour or object colour)
** 
** Reflect:
** R = 2 * (light_dir(normalized) * surface_normal) * Surface_normal - light_dir(normalized);
** 
** 
** 
** 
**  vec3 p = ro + rd * d; // point on surface found by ray marching
**       vec3 normal = calcNormal(p); // surface normal
** 
**       // light
**       vec3 lightPosition = vec3(-8, -6, -5);
**       vec3 lightDirection = normalize(lightPosition - p);
** 
**       // ambient
**       float k_a = 0.6;
**       vec3 i_a = vec3(0.7, 0.7, 0);
**       vec3 ambient = k_a * i_a;
** 
**       // diffuse
**       float k_d = 0.5;
**       float dotLN = clamp(dot(lightDirection, normal), 0., 1.);
**       vec3 i_d = vec3(0.7, 0.5, 0);
**       vec3 diffuse = k_d * dotLN * i_d;
** 
**       // specular
**       float k_s = 0.6;
**       float dotRV = clamp(dot(reflect(lightDirection, normal), -rd), 0., 1.);
**       vec3 i_s = vec3(1, 1, 1);
**       float alpha = 10.;
**       vec3 specular = k_s * pow(dotRV, alpha) * i_s;
** 
**       // final sphere color
**       col = ambient + diffuse + specular;
*/

