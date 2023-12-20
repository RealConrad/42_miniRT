#include "mini_rt.h"

char	**split_line(char *line)
{
	char	**tokens;
	char	*temp;
	int		i;

	i = 0;
	temp = ft_strdup(line);
	if (!temp)
		return (NULL);
	while (temp[i])
	{
		if (temp[i] == ',')
			temp[i] = ' ';
		else if (temp[i] == '\t')
			temp[i] = ' ';
		i++;
	}
	tokens = ft_split(temp, ' ');
	free(temp);
	if (!tokens)
		return (NULL);
	return (tokens);
}

void	free_2d_array(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
