#include "mini_rt.h"

static bool	is_valid_int(char *str, bool is_negative);

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
		printf("HELLO!\n");
		if (ft_strlen(tokens[1]) > 10 || ft_isstr(tokens[1], ft_isdigit) != 1)
			return (free_2d_array(tokens), false);
	}
	free_2d_array(tokens);
	return (true);
}

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
