/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:59:58 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/06 22:22:19 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (words);
}

static void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**ft_cpy_arr(char **arr, char const *s, char c, int words)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	while (i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		len = 0;
		while (s[j + len] && s[j + len] != c)
			len++;
		new_str = ft_substr(s, j, len);
		if (!new_str)
		{
			ft_free_split(arr);
			return (NULL);
		}
		arr[i] = new_str;
		j += len;
		i++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**arr;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	arr = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	arr = ft_cpy_arr(arr, s, c, words);
	if (!arr)
		return (NULL);
	arr[words] = NULL;
	return (arr);
}
