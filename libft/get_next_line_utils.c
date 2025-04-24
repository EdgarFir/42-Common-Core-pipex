/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:36:03 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/24 00:27:24 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_chr(const char *s, char c)
{
	int	len;

	len = 0;
	if (!c)
	{
		while (s[len])
			len++;
	}
	else
	{
		while (s[len] && s[len] != c)
			len++;
	}
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_p;
	unsigned char	*src_p;

	if (!dest && !src)
		return (NULL);
	dest_p = (unsigned char *)dest;
	src_p = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dest_p[i] = src_p[i];
		i++;
	}
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen_chr(s1, 0);
	s2_len = ft_strlen_chr(s2, 0);
	new_str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, s1_len);
	ft_memcpy(new_str + s1_len, s2, s2_len);
	new_str[s1_len + s2_len] = '\0';
	return (new_str);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	len = ft_strlen_chr(s, 0);
	new_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	s_len;

	if (!s || !len)
		return (NULL);
	s_len = ft_strlen_chr(s, 0);
	if (s_len < start)
	{
		sub_str = (char *)malloc(sizeof(char));
		if (!sub_str)
			return (NULL);
		sub_str[0] = '\0';
		return (sub_str);
	}
	if (len > s_len - start)
		len = s_len - start;
	sub_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_str)
		return (NULL);
	ft_memcpy(sub_str, s + start, len);
	sub_str[len] = '\0';
	return (sub_str);
}
