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
		dot = dot_product(ray->surface_norm, light_dir);
		if (light_hit(light_ray, scene->objects) && dot > 0.0)
		{
			diffuse = get_diffuse(scene, ray, dot);
			specular = get_specular(scene, ray, light_dir, dot);

			t_vector	temp_col;
			temp_col.x = (double)amb.r / 255 + (double)diffuse.r / 255 + (double)specular.r / 255;
			temp_col.y = (double)amb.g / 255 + (double)diffuse.g / 255 + (double)specular.g / 255;
			temp_col.z = (double)amb.b / 255 + (double)diffuse.b / 255 + (double)specular.b / 255;
			temp_col.x *= 255;
			temp_col.y *= 255;
			temp_col.z *= 255;
			ray->ray_colour.r = (int)temp_col.x;
			ray->ray_colour.g = (int)temp_col.y;
			ray->ray_colour.b = (int)temp_col.z;
			ray->ray_colour.r = clamp(amb.r + diffuse.r + specular.r, 0, 255);
			ray->ray_colour.g = clamp(amb.g + diffuse.g + specular.g, 0, 255);
			ray->ray_colour.b = clamp(amb.b + diffuse.b + specular.b, 0, 255);
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

	diffuse = colour_multiply(scene->light.colour, ray->ray_colour);
	diffuse = colour_scalar_multiply(diffuse, dot * scene->light.light_ratio);
	diffuse.r = (diffuse.r / 255.0) * (scene->light.light_ratio) * 255;
	diffuse.g = (diffuse.g / 255.0) * (scene->light.light_ratio) * 255;
	diffuse.b = (diffuse.b / 255.0) * (scene->light.light_ratio) * 255;
	return (diffuse);
}

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
	spec_intensity = pow(spec_angle, SHINY);
	specular = colour_scalar_multiply(scene->light.colour, spec_intensity);
	specular = colour_scalar_multiply(specular, scene->light.light_ratio);
	return (specular);

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
