
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

typedef struct s_cy_data
{
	t_vector	ray_origin_to_cy_center;
	double		quad_coeff_a;
	double		quad_coeff_b;
	double		quad_coeff_c;
	double		radius;
	double		discriminant;
	double		d0;
	double		d1;
	double		top_cap;
	double		bot_cap;
	bool		within_bounds_d0;
	bool		within_bounds_d1;
	bool		top_cap_hit;
	bool		bot_cap_hit;
}	t_cy_data;

/* ------------------------------- Environment ------------------------------ */

typedef struct s_amb_light
{
	double			light_ratio;
	t_colour		colour_in_range;
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