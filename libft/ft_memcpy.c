/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:17:41 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/08 22:52:50 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copy n bytes from src to dest
 * @param dest Pointer to copy to from src
 * @param src Pointer to be copied
 * @param n Number of bytes to be copied
 * @return Return dest
*/
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
