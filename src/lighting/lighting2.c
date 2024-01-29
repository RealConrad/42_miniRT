#include "mini_rt.h"

static t_colour	get_diffuse(t_scene *scene, t_ray *ray, double dot);
static t_colour	get_specular(t_scene *scene, t_ray *ray, t_vector light_dir, double dot);
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
			dot = fmax(dot_product(normalize_vector(ray->surface_norm), light_ray.direction), 0.0);

			diffuse = get_diffuse(scene, ray, dot);
			specular = get_specular(scene, ray, light_ray.direction, dot);

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

static t_colour	get_specular(t_scene *scene, t_ray *ray, t_vector light_dir, double dot)
{
	t_vector	reflection;
	t_vector	view_dir;
	t_colour	specular;
	double		spec_intensity;
	double		spec_angle;
	
	reflection = vec_subtract(vec_scalar_multiply(ray->surface_norm, 2 * dot), light_dir);
	view_dir = vec_scalar_multiply(ray->direction, -1.0);
	spec_angle = fmax(dot_product(view_dir, reflection), 0.0);
	spec_intensity = pow(spec_angle, 100); //TODO CHANHE
	specular = colour_scalar_multiply(normalize_colour(scene->light.colour), spec_intensity);
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
		if (distance > 0.0 && distance < vec_length(vec_subtract(light.cords, ray.origin)) + EPSILON)
			return (false);
		temp = temp->next;
	}
	return (true);
}

/**
 * 
 *         if (distance > EPSILON) // Check if there is a valid intersection
        {
            t_vector intersection_point = ray_at(ray, distance);

            // Calculate the vector from the intersection point to the light source
            t_vector to_light_source = vec_subtract(ray.hit_point, intersection_point);
            
            // Check if the intersection point is in front of the light source
            double dp = dot_product(to_light_source, ray.direction);
            
            if (dp > 0.0)
            {
                // The intersection point is in the direction of the light source
                // and not behind it, so it's not in shadow
                return false;
            }
        }
*/

static t_ray	get_light_ray(t_light light, t_vector hit_point)
{
	t_ray	light_ray;

	light_ray.origin = hit_point;
	light_ray.direction = vec_subtract(light.cords, hit_point);
	light_ray.direction = normalize_vector(light_ray.direction);
	// light_ray.origin = vec_add(light_ray.origin, vec_scalar_multiply(light_ray.direction, EPSILON));
	light_ray.hit_point = light.cords;
	// printf("Light ray origin: ");
	// t_print_vector(light_ray.origin);
	// printf("Light ray dir: ");
	// t_print_vector(light_ray.direction);
	// printf("Light ray hit: ");
	// t_print_vector(light_ray.hit_point);
	return (light_ray);
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

