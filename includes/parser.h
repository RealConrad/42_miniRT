
#ifndef PARSER_H
# define PARSER_H

# include <stdint.h>

/* -------------------------------------------------------------------------- */
/*                                   Structs                                  */
/* -------------------------------------------------------------------------- */

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

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

t_scene		parser(int argc, char *argv[]);
void		parser_exit(int error_code, void **free_me);
void		free_objects(t_object **objects);
void		analize_line(char *line, t_scene *scene, int fd);
bool		atof_check(char *str);
bool		atoi_check(char *str);
void		free_split(char **split);
t_colour	get_colour_input(char **split, int colour_index);
bool		legal_colour(t_colour colour);
t_vector	get_vector_input(char **split, int vec_index);
bool		legal_vector(t_vector vector, double min, double max);
bool		legal_vector_input(char **split, int vec_index);
void		exit_analize(char *line, t_scene *scene, int fd, char **split);
void		add_object_to_linked_list(t_scene *scene, t_object *object);

#endif /*PARSER_H*/