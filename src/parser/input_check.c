#include "mini_rt.h"

static bool	is_valid_int(char *str, bool is_negative);

/**
 * @brief Checks if all the strings are valid numbers
 * 
 * The function iterates through the 2D string array (starting from the second index).
 * We skip the first index because it will be the type of element, 
 * e.g. `C` for the camera.
 * @param tokens An array of tokens to be checked.
 * @return `True` if all tokens from the 2nd element onwards are valid numbers,
 * else `False`.
 */
bool	is_valid_numbers(char **tokens)
{
	int	i;

	i = 1;
	while (tokens[i])
	{
		if (!atof_check(tokens[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Validates if a string is a properly formatted float number.
 * @param str The string to be checked.
 * @return `True` if the string represents a valid float number, else `false`.
 */
bool	atof_check(char *str)
{
	char	**tokens;
	char	*temp;
	bool	is_negative;

	tokens = ft_split(str, '.');
	if (!tokens)
		return (false);
	temp = tokens[0];
	if (temp[0] == '-')
	{
		is_negative = true;
		temp++;
	}
	else
		is_negative = false;
	if (!is_valid_int(temp, is_negative))
		return (free_2d_array(tokens), false);
	if (tokens[1])
	{
		if (ft_strlen(tokens[1]) > 10 || ft_isstr(tokens[1], ft_isdigit) != 1)
			return (free_2d_array(tokens), false);
	}
	free_2d_array(tokens);
	return (true);
}

/**
 * @brief Checks if the given colour is in the correct range (0-255).
 * @param colour The colour to check.
 * @return `True` if all colours (red, blue, green) are within the range 0-255,
 * else `false`.
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
 * @brief Checks if the string is a valid int.
 * @param str The string to be checked.
 * @param is_negative A boolean indicating if the number is negative or not.
 * @return `True` if the string is a valid int, else `false`.
 */
static bool	is_valid_int(char *str, bool is_negative)
{
	int		len;
	char	*max;

	if (ft_isstr(str, ft_isdigit) != 1)
		return (false);
	len = ft_strlen(str);
	if (len > 10)
		return (false);
	if (is_negative)
		max = "2147483648";
	else
	{
		max = "2147483647";
		if (len == 10 && ft_strncmp(str, max, 10) > 10)
			return (false);
	}
	return (true);
}
