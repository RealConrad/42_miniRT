#include "mini_rt.h"

void	assign_vector(t_vector *vector, char **tokens, int start_index)
{
	vector->x = ft_atof(tokens[start_index]);
	vector->y = ft_atof(tokens[start_index + 1]);
	vector->z = ft_atof(tokens[start_index + 2]);
}

void	assign_colour(t_colour *colour, char **tokens, int start_index)
{
	colour->r = ft_atoi(tokens[start_index]);
	colour->g = ft_atoi(tokens[start_index + 1]);
	colour->b = ft_atoi(tokens[start_index + 2]);
}
