#include "mini_rt.h"

static t_colour	get_diffuse(t_scene *scene, t_ray *ray, double dot);
static t_colour	get_specular(t_scene *scene, t_ray *ray, t_vector light_dir, double dot);
static bool		light_hit(t_ray ray, t_object *objects);
static t_ray	get_light_ray(t_light light, t_vector hit_point);

void	lighting2(t_scene *scene, t_ray *ray)
{
	t_colour	amb;
	t_colour	diffuse;
	t_colour	specular;
	t_vector	light_dir;
	double		dot;
	t_ray		light_ray;

	if (ray->distance >= 0)
	{
		amb = get_ambient_light(ray->ray_colour, scene->amb_light);
		light_ray = get_light_ray(scene->light, ray->hit_point);
		light_dir = normalize_vector(vec_subtract(scene->light.cords, ray->hit_point));
		if (light_hit(light_ray, scene->objects))
		{
			dot = fmax(dot_product(ray->surface_norm, light_dir), 0.0);
			diffuse = get_diffuse(scene, ray, dot);
			specular = get_specular(scene, ray, light_dir, dot);

			ray->ray_colour.r = amb.r + diffuse.r + specular.r;
			ray->ray_colour.g = amb.g + diffuse.g + specular.g;
			ray->ray_colour.b = amb.b + diffuse.b + specular.b;
			clamp_normalized_colour(&ray->ray_colour);
		}
		else
			ray->ray_colour = amb;
	}
	else
		ray->ray_colour = get_sky_background(ray);
}


static t_colour	get_diffuse(t_scene *scene, t_ray *ray, double dot)
{
	t_colour	diffuse;

	diffuse.r = ray->ray_colour.r * dot * scene->light.light_ratio * ray->ray_colour.r;
	diffuse.g = ray->ray_colour.g * dot * scene->light.light_ratio * ray->ray_colour.g;
	diffuse.b = ray->ray_colour.b * dot * scene->light.light_ratio * ray->ray_colour.b;
	return (diffuse);
}

// Helper function to reflect a vector around a normal
// t_vector reflect(t_vector v, t_vector normal) {
//     return vec_subtract(vec_scalar_multiply(normal, 2 * dot_product(normal, v)), v);
// }

// t_vector vec_negate(t_vector v) {
//     t_vector negated;
//     negated.x = -v.x;
//     negated.y = -v.y;
//     negated.z = -v.z;
//     return negated;
// }

// static t_colour get_specular(t_scene *scene, t_ray *ray, t_vector light_dir, double dot) {
//     t_vector reflection;
//     t_vector view_dir;
//     t_colour specular;
//     double spec_intensity;
//     double spec_angle;

//     // Correct the light direction and calculate the reflection vector
//     light_dir = vec_negate(normalize_vector(light_dir));  // Negate and normalize light direction
//     reflection = reflect(light_dir, ray->surface_norm);

//     // Correct the view direction calculation
//     view_dir = normalize_vector(vec_subtract(ray->hit_point, ray->origin));

//     // Calculate the specular angle and intensity
//     spec_angle = fmax(dot_product(view_dir, reflection), 0.0);
//     spec_intensity = pow(spec_angle, SHINY);

//     // Normalize the light color and calculate the specular color
//     t_colour normalized_light_color = normalize_colour(scene->light.colour);
//     specular = colour_scalar_multiply(normalized_light_color, spec_intensity);
//     specular = colour_scalar_multiply(specular, scene->light.light_ratio);
// 	(void)dot;
//     return specular;
// }

static t_colour	get_specular(t_scene *scene, t_ray *ray, t_vector light_dir, double dot)
{
	t_vector	reflection;
	t_vector	view_dir;
	t_colour	specular;
	double		spec_intensity;
	double		spec_angle;
	
	reflection = vec_subtract(vec_scalar_multiply(ray->surface_norm, 2 * dot), light_dir);
	view_dir = normalize_vector(vec_subtract(ray->origin, ray->hit_point));
	spec_angle = fmax(dot_product(view_dir, reflection), 0.0);
	spec_intensity = pow(spec_angle, 300); //TODO CHANHE
	specular = colour_scalar_multiply(normalize_colour(scene->light.colour), spec_intensity);
	specular = colour_scalar_multiply(specular, scene->light.light_ratio);
	return (specular);
}

static bool	light_hit(t_ray ray, t_object *objects)
{
	t_object	*temp;
	double		distance;

	temp = objects;
	while (temp != NULL)
	{
		distance = hit_object(temp, &ray);
		if (distance > 0.0 && distance < vec_length(vec_subtract(ray.hit_point, ray.origin)) + EPSILON)
			return (false);
		temp = temp->next;
	}
	return (true);
}

static t_ray	get_light_ray(t_light light, t_vector hit_point)
{
	t_ray	light_ray;

	light_ray.origin = hit_point;
	light_ray.direction = vec_subtract(light.cords, hit_point);
	light_ray.direction = normalize_vector(light_ray.direction);
	light_ray.hit_point = light.cords;
	if (hit_point.y > light.cords.y)
		light_ray.direction.y *= -1;
	return (light_ray);
}
