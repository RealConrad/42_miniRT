/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_blank.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eweiberl <eweiberl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:41:01 by eweiberl          #+#    #+#             */
/*   Updated: 2023/12/14 15:16:52 by eweiberl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini_rt.h"

static size_t	count_substr(char const *s);
static char		*getstr(char const *s, size_t i);
static void		free_strings(void **strings, size_t size);
static size_t	next_pos(char const *s, size_t i);

/**
 * @brief Splits a string by blanks
 * @param s 
 * @return an array of splitted strings, NULL on malloc fail
 */
char	**ft_split_blank(char const *s)
{
	size_t	substr_ctr;
	size_t	substr_fnd;
	size_t	pos_in_str;
	char	**strings;

	substr_fnd = 0;
	pos_in_str = 0;
	substr_ctr = count_substr(s);
	strings = (char **)ft_calloc(substr_ctr + 1, sizeof(char *));
	if (!strings || !s)
		return (NULL);
	while (substr_fnd < substr_ctr)
	{
		pos_in_str = next_pos(s, pos_in_str);
		strings[substr_fnd] = getstr(s, pos_in_str);
		if (!strings[substr_fnd])
		{
			free_strings((void **)strings, substr_fnd);
			return (NULL);
		}
		pos_in_str = pos_in_str + ft_strlen(strings[substr_fnd]);
		substr_fnd++;
	}
	strings[substr_fnd] = NULL;
	return (strings);
}

static char	*getstr(char const *s, size_t i)
{
	size_t	start;
	char	*str;

	while (ft_isblank(s[i]) == 1 && s[i])
		i++;
	start = i;
	while (ft_isblank(s[i]) != 1 && s[i] != '\0')
		i++;
	str = ft_substr(s, start, (i - start));
	if (!str)
		return (NULL);
	return (str);
}

static size_t	count_substr(char const *s)
{
	size_t	i;
	size_t	ctr;

	i = 0;
	ctr = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		while (ft_isblank(s[i]) == 1 && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			ctr++;
		while (ft_isblank(s[i]) != 1 && s[i] != '\0')
			i++;
	}
	return (ctr);
}

static void	free_strings(void **strings, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

static size_t	next_pos(char const *s, size_t i)
{
	while (ft_isblank(s[i]) == 1 && s[i])
		i++;
	return (i);
}
