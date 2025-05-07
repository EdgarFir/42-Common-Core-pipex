/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrei10 <edrei10@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:02:37 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/04 23:34:56 by edrei10          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_from_set(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	s1_len;
	unsigned int	new_str_start;
	unsigned int	new_str_end;
	unsigned int	new_str_len;
	char			*new_str;

	s1_len = ft_strlen(s1);
	if (!s1_len)
	{
		new_str = ft_strdup(s1);
		if (!new_str)
			return (NULL);
		return (new_str);
	}
	new_str_start = 0;
	while (is_from_set(set, s1[new_str_start]) && s1[new_str_start])
		new_str_start++;
	new_str_end = s1_len - 1;
	while (is_from_set(set, s1[new_str_end]) && new_str_end > new_str_start)
		new_str_end--;
	new_str_len = (new_str_end + 1) - new_str_start;
	new_str = ft_substr(s1, new_str_start, new_str_len);
	if (!new_str)
		return (NULL);
	return (new_str);
}
