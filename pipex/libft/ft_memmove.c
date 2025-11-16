/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:16:30 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/09 11:33:24 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies n bytes from src to dest. Memory of dest and src may overlap. 
 * Use memmove if memory areas overlap else use memcpy
 * @param dest Pointer to dest that will receive bytes from src 
 * @param src  Pointer to src whtat will be copied to dest
 * @param n Number of bytes that will be copied
 * @return Pointer to dest
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*dest_p;
	const char	*src_p;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	dest_p = dest;
	src_p = src;
	if (dest_p < src_p)
	{
		ft_memcpy(dest, src, n);
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			dest_p[i] = src_p[i];
		}
	}
	return (dest);
}
