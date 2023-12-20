
#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>

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

typedef struct s_scene
{
	t_amb_light		amb_light;
	t_camera		camera;
	t_light			light;
	t_object		*objects;
}	t_scene;

#endif 