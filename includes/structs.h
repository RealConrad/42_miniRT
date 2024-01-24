
#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>

enum e_exit_msg
{
	NORMAL = 0,
	MALLOC_FAIL,
	OPEN_FAIL,
	INPUT_FILE,
	INPUT_MISSING,
	DUPLICATED,
	MISSING,
	FORMAT
};

typedef enum e_object_type
{
	SPHERE,
	CYLINDER,
	PLANE
}	t_object_type;


/* ------------------------------ Vector/Colour ----------------------------- */
typedef struct s_colour
{
	int				r;
	int				g;
	int				b;
}	t_colour;

typedef struct s_vector
{
	double			x;
	double			y;
	double			z;
}	t_vector;

/**
 * @brief Cylinder data struct
 * @param x ector difference between the ray origin and cylinder center
 * @param d Ray direction (normalized)
 * @param v Cylinder axis (normalized)
 * @param a Coefficient `a` in quadratic equation for intersection
 * @param b Coefficient `b` in quadratic equation for intersection
 * @param c Coefficient `c` in quadratic equation for intersection
 * @param radius Radius of the cylinder
 * @param discriminant Result of quadratic equation, used to determine intersections
 * @param d0 Distance of first potentional intersection
 * @param d_top_cap Distance to the top caps intersection
 * @param d_bot_cap Distance to bot caps intersection
 * @param within_bounds_d0 Used to determine if `d0` is within cy bounds
 * @param hit_top_cap Boolean indicating if top cap is intersected
 * @param hit_bot_cap Boolean indicating if bot cap is intersected
 */
typedef struct s_cy_data
{
	t_vector	x;
	t_vector	d;
	t_vector	v;
	double		a;
	double		b;
	double		c;
	double		radius;
	double		discriminant;
	double		d0;
	double		d_top_cap;
	double		d_bot_cap;
	bool		within_bounds_d0;
	bool		hit_top_cap;
	bool		hit_bot_cap;
}	t_cy_data;

/* ------------------------------- Environment ------------------------------ */

typedef struct s_amb_light
{
	double			light_ratio;
	t_colour		colour;
}	t_amb_light;

typedef struct s_camera
{
	t_vector		cords;
	t_vector		or_vect;
	int				fov;
}	t_camera;

typedef struct s_light
{
	t_vector		cords;
	double			light_ratio;
	t_colour		colour;
}	t_light;

/* --------------------------------- Objects -------------------------------- */

typedef struct s_sphere
{
	t_vector		cords;
	double			diameter;
	t_colour		colour;
}	t_sphere;

typedef struct s_plane
{
	t_vector		cords;
	t_vector		threed_vec;
	t_colour		colour;
}	t_plane;

typedef struct s_cylinder
{
	t_vector		cords;
	t_vector		axis;
	double			diameter;
	double			height;
	t_colour		colour;
}	t_cylinder;

typedef struct s_object
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	struct s_object	*next;
}	t_object;

/* ----------------------------------- Ray ---------------------------------- */
typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
	t_vector	hit_point;
	double		distance;
	t_vector	surface_norm;
	t_colour	ray_colour;
}	t_ray;

/* -------------------------------- Viewport -------------------------------- */

typedef struct s_viewport
{
	t_vector	camera_direction;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	upper_left_corner;
	t_vector	pixel00_loc;
}	t_viewport;

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_amb_light		amb_light;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
}	t_scene;

#endif