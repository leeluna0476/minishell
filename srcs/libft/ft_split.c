/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojilee <seojilee@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 02:21:05 by seojilee          #+#    #+#             */
/*   Updated: 2023/10/17 13:50:01 by seojilee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *str, char c)
{
	int	i;
	int	words;

	i = 1;
	if (str[0] == '\0' || str[0] == c)
		words = 0;
	else
		words = 1;
	while (str[i])
	{
		if (str[i - 1] == c && str[i] != c)
			words++;
		i++;
	}
	return (words);
}

static char	*ft_strdup2(char const *src, int start, int end)
{
	char	*str;
	int		i;

	str = ft_calloc(end - start + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
	{
		str[i] = src[start];
		i++;
		start++;
	}
	return (str);
}

static char	**ft_free_all(char **strings)
{
	size_t	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;
	size_t	i;
	size_t	j;
	int		temp;

	if (!s)
		return (NULL);
	strings = ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!strings)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words(s, c) && s[i])
	{
		while (s[i] == c && s[i])
			i++;
		temp = i;
		while (s[i] != c && s[i])
			i++;
		strings[j] = ft_strdup2(s, temp, i);
		if (!strings[j])
			return (ft_free_all(strings));
		j++;
	}
	return (strings);
}
