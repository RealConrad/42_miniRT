
#ifndef PARSER_H
# define PARSER_H

# include "mini_rt.h"

/* -------------------------------------------------------------------------- */
/*                                  Functions                                 */
/* -------------------------------------------------------------------------- */

char		**split_line(char *line);
t_scene		parser(char **argv);
void		parser_exit(int error_code, void **free_me);
void		free_2d_array(char **tokens);
bool		atof_check(char *str);
bool		is_valid_numbers(char **tokens);
bool		legal_colour(t_colour colour);
void		exit_analyse(t_scene *scene, char **tokens,
				int fd, t_object *object);
void		init_amb(t_scene *scene, char **tokens, int fd);
void		init_cam(t_scene *scene, char **tokens, int fd);
void		init_light(t_scene *scene, char **tokens, int fd);
bool		legal_vector(t_vector vector, double min, double max);
void		init_plane(t_scene *scene, char **tokens, int fd);
void		init_cylinder(t_scene *scene, char **tokens, int fd);
void		init_sphere(t_scene *scene, char **tokens, int fd);
void		assign_vector(t_vector *vector, char **tokens, int start_index);
void		assign_colour(t_colour *colour, char **tokens, int start_index);

#endif /*PARSER_H*/