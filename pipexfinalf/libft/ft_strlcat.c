/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrei10 <edrei10@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:30:39 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/04 22:00:40 by edrei10          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;
	size_t	len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	len = 0;
	if (size <= dst_len)
		return (src_len + size);
	else
		len = dst_len + src_len;
	while (src[i] && (dst_len + 1) < size)
	{
		dst[dst_len] = src[i];
		dst_len++;
		i++;
	}
	dst[dst_len] = '\0';
	return (len);
}
