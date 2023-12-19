
#include "mini_rt.h"

/**
 * @brief Checks if atoi would overflow
 * @param str 
 * @return true if atoi works fine, false if overflow
 */
bool	atoi_check(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (ft_strlen(str + i) > 10)
		return (false);
	if (ft_strlen(str + i) == 10)
		if ((i == 0 && ft_strncmp(str, "2147483647", 10) > 0)
			|| (i == 1 && ft_strncmp(str + 1, "2147483648", 10) > 0))
			return (false);
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) != 1)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Checks if atof would overflow
 * @param str 
 * @return true if atof works fine, false if overflow
 */
bool	atof_check(char *str)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split(str, '.');
	if (split == NULL)
		return (false);
	if (!split[0] || (split[1] && split[2] != NULL))
		return (free_split(split), false);
	if (split[0][0] == '-')
		i++;
	if (ft_strlen(split[0] + i) > 10)
		return (free_split(split), false);
	if (ft_strlen(split[0] + i) == 10)
		if ((i == 0 && ft_strncmp(split[0], "2147483647", 10) > 0)
			|| (i == 1 && ft_strncmp(split[0] + 1, "2147483648", 10) > 0))
			return (free_split(split), false);
	if (ft_isstr(split[0] + i, ft_isdigit) != 1)
		return (free_split(split), false);
	if (split[1] != NULL)
		if (ft_strlen(split[1]) > 10 || ft_isstr(split[1], ft_isdigit) != 1
			|| ft_strncmp(split[1], "2147483647", 10) > 0)
			return (free_split(split), false);
	return (free_split(split), true);
}

void	free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}
