/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:03:56 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/08 23:02:14 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	str = (char *)s + s_len;
	i = 0;
	while (i <= s_len && *(unsigned char *)str != (char)c)
	{
		str--;
		i++;
	}
	if (i <= s_len)
		return (str);
	return (NULL);
}
