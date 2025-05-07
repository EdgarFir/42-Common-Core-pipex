/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_conv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:23:57 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/24 00:38:44 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_valid_conv(const char *str)
{
	char	*conv;

	conv = "cspdiuxX%";
	if (!str[0] || !str[1])
		return (0);
	if (str[0] == '%' && ft_strchr(conv, str[1]))
		return (1);
	return (0);
}
