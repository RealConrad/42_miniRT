
#include "../../includes/mini_rt.h"

/**
 * @brief Gets the colour values of the input
 * @param split 
 * @param colour_index the start index in split of the colour values
 * @return a colour struct, one val=-1 on failure
 */
t_colour	get_colour_input(char **split, int colour_index)
{
	t_colour	colour;
	char		**clr_split;

	colour.r = -1;
	if (ft_strchr(split[colour_index], ',' ) != NULL)
	{
		clr_split = ft_split(split[colour_index], ',');
		if (!clr_split || !clr_split[0] || !clr_split[1] || !clr_split[2]
			|| clr_split[3] != NULL)
			return (free_split(clr_split), colour);
		if (!atoi_check(clr_split[0]) || !atoi_check(clr_split[1])
			|| !atoi_check(clr_split[2]))
			return (free_split(clr_split), colour);
		colour.r = ft_atoi(clr_split[0]);
		colour.g = ft_atoi(clr_split[1]);
		colour.b = ft_atoi(clr_split[2]);
		return (free_split(clr_split), colour);
	}
	if (!atoi_check(split[colour_index]) || !atoi_check(split[colour_index + 1])
		|| !atoi_check(split[colour_index + 2]))
		return (colour);
	colour.r = ft_atoi(split[colour_index]);
	colour.g = ft_atoi(split[colour_index + 1]);
	colour.b = ft_atoi(split[colour_index + 2]);
	return (colour);
}

/**
 * @brief Checks if the colour value is between 0 and 255
 * @param colour 
 * @return true if it is in range, false
 */
bool	legal_colour(t_colour colour)
{
	if (colour.r > 255 || colour.r < 0)
		return (false);
	if (colour.g > 255 || colour.g < 0)
		return (false);
	if (colour.b > 255 || colour.b < 0)
		return (false);
	return (true);
}

/**
 * @brief Checks if the vector is legal
 * @param vector the vector to check
 * @param min the minimal value
 * @param max the max value
 * @return true if in range, false
 */
bool	legal_vector(t_vector vector, double min, double max)
{
	if (vector.x < min || vector.x > max)
		return (false);
	if (vector.y < min || vector.y > max)
		return (false);
	if (vector.z < min || vector.z > max)
		return (false);
	return (true);
}

/**
 * @brief Gets the input of a vector
 * @param split 
 * @param vec_index the start index in the split
 * @return NULL on failure, the vector
 */
t_vector	*get_vector_input(char **split, int vec_index)
{
	t_vector	vector;
	char		**vec_split;

	if (ft_strchr(split[vec_index], ',' ) != NULL)
	{
		vec_split = ft_split(split[vec_index], ',');
		if (!vec_split || !vec_split[0] || !vec_split[1] || !vec_split[2]
			|| vec_split[3] != NULL)
			return (free_split(vec_split), NULL);
		if (!atof_check(vec_split[0]) || !atof_check(vec_split[1])
			|| !atof_check(vec_split[2]))
			return (free_split(vec_split), NULL);
		vector.x = ft_atof(vec_split[0]);
		vector.y = ft_atof(vec_split[1]);
		vector.z = ft_atof(vec_split[2]);
		return (free_split(vec_split), &vector);
	}
	if (!atof_check(split[vec_index]) || !atof_check(split[vec_index + 1])
		|| !atoi_check(split[vec_index + 2]))
		return (NULL);
	vector.x = ft_atoi(split[vec_index]);
	vector.y = ft_atoi(split[vec_index + 1]);
	vector.z = ft_atoi(split[vec_index + 2]);
	return (&vector);
}
