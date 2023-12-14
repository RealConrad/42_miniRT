
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
	if (ft_strchr(split[colour_index], ',' )!= NULL)
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
