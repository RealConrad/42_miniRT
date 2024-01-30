/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 16:46:09 by eweiberl          #+#    #+#             */
/*   Updated: 2024/01/30 16:46:11 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/**
 * @brief Splits a stringi nto an array of tokens based on certain
 * delimiters
 * 
 * This function duplicates the given `line` and replaces all `commas`
 * and `tabs` with a `single space`. It then splits the string based on spaces
 * @param line The string to be split into tokens
 * @return The newly created array of tokens, or `NULL` if the line
 * cannot be duplicated or if splitting fails.
 * @note The caller is responsible for freeing the memory
 * allocated for the tokens.
 */
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

/**
 * @brief Frees a 2 dimensional array of strings
 * @param tokens The 2D array to be freed.
 */
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
