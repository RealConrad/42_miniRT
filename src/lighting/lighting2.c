#include "mini_rt.h"

static t_colour	get_diffuse(t_scene *scene, t_ray *ray, double dot);
static t_colour	get_specular(t_scene *scene, t_ray *ray,
					t_vector light_dir, double dot);
static bool		light_hit(t_ray ray, t_object *objects, t_light light);
static t_ray	get_light_ray(t_light light, t_vector hit_point);

void	lighting2(t_scene *scene, t_ray *ray)
{
	t_colour	amb;
	t_colour	diffuse;
	t_colour	specular;
	double		dot;
	t_ray		light_ray;

	if (ray->distance >= 0)
	{
		amb = get_ambient_light(ray->ray_colour, scene->amb_light);
		light_ray = get_light_ray(scene->light, ray->hit_point);
		if (light_hit(light_ray, scene->objects, scene->light))
		{
			dot = fmax(dot_product(normalize_vector(ray->surface_norm),
						light_ray.direction), 0.0);
			diffuse = get_diffuse(scene, ray, dot);
			specular = get_specular(scene, ray, light_ray.direction, dot);
			ray->ray_colour = add_phong_elements(amb, diffuse, specular);
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

	diffuse.r = ray->ray_colour.r * dot * scene->light.light_ratio
		* ray->ray_colour.r;
	diffuse.g = ray->ray_colour.g * dot * scene->light.light_ratio
		* ray->ray_colour.g;
	diffuse.b = ray->ray_colour.b * dot * scene->light.light_ratio
		* ray->ray_colour.b;
	return (diffuse);
}

static t_colour	get_specular(t_scene *scene, t_ray *ray, t_vector light_dir,
		double dot)
{
	t_vector	reflection;
	t_vector	view_dir;
	t_colour	specular;
	double		spec_intensity;
	double		spec_angle;

	reflection = vec_subtract(vec_scalar_multiply(ray->surface_norm, 2 * dot),
			light_dir);
	view_dir = vec_scalar_multiply(ray->direction, -1.0);
	spec_angle = fmax(dot_product(view_dir, reflection), 0.0);
	spec_intensity = pow(spec_angle, SHINY);
	specular = colour_scalar_multiply(normalize_colour(scene->light.colour),
			spec_intensity);
	specular = colour_scalar_multiply(specular, scene->light.light_ratio);
	return (specular);
}

static bool	light_hit(t_ray ray, t_object *objects, t_light light)
{
	t_object	*temp;
	double		distance;

	temp = objects;
	while (temp != NULL)
	{
		distance = hit_object(temp, &ray);
		if (distance > 0.0 && distance
			< vec_length(vec_subtract(light.cords, ray.origin)) + EPSILON)
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
	return (light_ray);
}
