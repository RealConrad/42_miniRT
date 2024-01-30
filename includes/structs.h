
#ifndef STRUCTS_H
# define STRUCTS_H

# include "mini_rt.h"

/* ---------------------------------- Enums --------------------------------- */

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

/**
 * @brief An object identifier
*/
typedef enum e_object_type
{
	SPHERE,
	CYLINDER,
	PLANE
}	t_object_type;


/* ------------------------------ Vector/Colour ----------------------------- */

/**
 * @brief A colour datastruct
 * @note Can either be normalized between 0 and 1 or a rgb colour
 * @param r the red channel
 * @param g the green channel
 * @param b the blue channel
*/
typedef struct s_colour
{
	double				r;
	double				g;
	double				b;
}	t_colour;

/**
 * @brief A vector datastruct
 * @note Can either be normalized between -1 and 1 or a point
 * @param x Coordinate (left-right)
 * @param y Coordinate (down-up)
 * @param z Coordinate (back-forth)
*/
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
 * @param discriminant Result of quadratic equation,
 * used to determine intersections
 * @param d0 Distance of first potentional intersection
 * @param d_top_cap Distance to the top caps intersection
 * @param d_bot_cap Distance to bot caps intersection
 * @param within_bounds_d0 Used to determine if `d0`
 * is within cy bounds
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

/**
 * @brief Stores the ambient light data
 * @param light_ratio the factor (0, 1) the ambient light should be applied with
 * @param colour_in_range the maximum strengh the ambient light
 * will give each channel
*/
typedef struct s_amb_light
{
	double			light_ratio;
	t_colour		colour_in_range;
}	t_amb_light;

/**
 * @brief Stores the camera data
 * @param cords the position of the camera
 * @param or_vec the orientation of the camera (normalized between -1 and 1)
 * @param fov the field of view of the camera
*/
typedef struct s_camera
{
	t_vector		cords;
	t_vector		or_vect;
	int				fov;
}	t_camera;

/**
 * @brief Stores the light data
 * @param cords the position of the light
 * @param light_ratio the factor the light will be applied witb (0, 1)
 * @param colour the colour of the light
*/
typedef struct s_light
{
	t_vector		cords;
	double			light_ratio;
	t_colour		colour;
}	t_light;

/* --------------------------------- Objects -------------------------------- */

/**
 * @brief Stores the data of one sphere object
 * @param cords the position of the sphere center
 * @param diameter the diameter of the sphere
 * @param colour the colour of the sphere
*/
typedef struct s_sphere
{
	t_vector		cords;
	double			diameter;
	t_colour		colour;
}	t_sphere;

/**
 * @brief Stores the data of one plane object
 * @param cords the position of one point in the plane
 * @param theed_vec the orientation of the plane (normalized between -1, 1)
 * @param colour the colour of the plane
*/
typedef struct s_plane
{
	t_vector		cords;
	t_vector		threed_vec;
	t_colour		colour;
}	t_plane;

/**
 * @brief Stores the data of one cylinder object
 * @param cords the position of the center point of the cylinder
 * @param axis the normalized (-1, 1) orientation of the cylinder
 * @param diameter the diameter (width) of the cylinder
 * @param height the height of the cylinder
 * @param colour the colour of the cylinder
*/
typedef struct s_cylinder
{
	t_vector		cords;
	t_vector		axis;
	double			diameter;
	double			height;
	t_colour		colour;
}	t_cylinder;

/**
 * @brief A linked list storing all objects
 * @note Only one object per node (to NULL pointers)
 * @param sphere pointer to a sphere object
 * @param plane pointer to a plane objext
 * @param cylinder pointer to a cylinder object
 * @param next pointer to the next node containig ONE other object
 * or NULL if on the last node
*/
typedef struct s_object
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	struct s_object	*next;
}	t_object;

/* ----------------------------------- Ray ---------------------------------- */

/**
 * @brief Stores the data of a ray
 * @param origin the origin point of a ray, will either be the camera
 * or the hit point on an object (for shadow rays)
 * @param direction the directional vector of a ray (normalized between -1, 1)
 * @param hit_point the point where the ray hits either a surface
 * or the light (for a shadow ray)
 * @param distance the distance between origin and hit_point
 * @param surface_norm the surface normal of the object on the hit_point
 * will be uninitialized for shadow rays
 * @param ray_colour the colour of a ray
 * (all the light a the hitpoint of the ray from the camera)
*/
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
	double		aspect_ratio;
	double		focal_length;
	double		height;
	double		width;
	t_vector	delta_u;
	t_vector	delta_v;
	t_vector	pixel00_loc;
}	t_viewport;

/**
 * @brief Stores all the scene values
 * @param mlx the mlx window pointer
 * @param img the image returned from the mlx
 * @param amb_light the ambient light struct
 * @param camera the camera struct
 * @param light the light struct
 * @param objects the linked list off all the objects
*/
typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_amb_light		amb_light;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
	t_viewport		viewport;
	long			core_num;
}	t_scene;

#endif