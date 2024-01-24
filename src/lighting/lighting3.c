#include "mini_rt.h"

static t_colour colour_multiply(t_colour c1, t_colour c2);
static t_colour colour_scalar_multiply(t_colour c, double scalar);

void	lighting3(t_scene *scene, t_ray *ray)
{
	t_colour	amb;
	t_colour	diffuse;
	t_vector	light_dir;
	double		dot;

	t_colour	specular;
	double		shiny = 10;

	amb.r = (ray->ray_colour.r / 255.0 * scene->amb_light.colour.r / 255.0) * scene->amb_light.light_ratio;
	amb.g = (ray->ray_colour.g / 255.0 * scene->amb_light.colour.g / 255.0) * scene->amb_light.light_ratio;
	amb.b = (ray->ray_colour.b / 255.0 * scene->amb_light.colour.b / 255.0) * scene->amb_light.light_ratio;
	amb.r *= 255;
	amb.g *= 255;
	amb.b *= 255;

	// hits object
	if (ray->distance >= 0)
	{
		light_dir = normalize_vector(vec_subtract(scene->light.cords, ray->hit_point));
		dot = dot_product(ray->surface_norm, light_dir);
		if (dot > 0)
		{
			diffuse = colour_multiply(scene->light.colour, ray->ray_colour);
			diffuse = colour_scalar_multiply(diffuse, dot * scene->light.light_ratio);
			
			// Calculate reflection vector
        	t_vector reflection = vec_subtract(vec_scalar_multiply(ray->surface_norm, 2 * dot), light_dir);
        	// Calculate view direction (from hit point to camera)
        	t_vector view_dir = normalize_vector(vec_subtract(ray->origin, ray->hit_point));
        	// Calculate dot product between view direction and reflection vector
        	double spec_angle = fmax(dot_product(view_dir, reflection), 0.0);
        	// Calculate specular intensity
        	double spec_intensity = pow(spec_angle, shiny);
        	// Calculate specular color
        	specular = colour_scalar_multiply(scene->light.colour, spec_intensity);

        	// Combine specular with ambient and diffuse
        	ray->ray_colour.r = clamp(amb.r + diffuse.r + specular.r, 0, 255);
        	ray->ray_colour.g = clamp(amb.g + diffuse.g + specular.g, 0, 255);
        	ray->ray_colour.b = clamp(amb.b + diffuse.b + specular.b, 0, 255);
		}
		else
			ray->ray_colour = amb;
	}
	else
	{
		// background
		ray->ray_colour = get_ambient_light(scene->amb_light, (t_colour){255, 255, 255});
	}
}

static t_colour colour_multiply(t_colour c1, t_colour c2)
{
	t_colour result;

	result.r = (c1.r / 255.0 * c2.r / 255.0) * 255;
	result.g = (c1.g / 255.0 * c2.g / 255.0) * 255;
	result.b = (c1.b / 255.0 * c2.b / 255.0) * 255;
	return result;
}

static t_colour colour_scalar_multiply(t_colour c, double scalar)
{
	t_colour result;

	result.r = clamp(c.r * scalar, 0, 255);
	result.g = clamp(c.g * scalar, 0, 255);
	result.b = clamp(c.b * scalar, 0, 255);
	return result;
}
