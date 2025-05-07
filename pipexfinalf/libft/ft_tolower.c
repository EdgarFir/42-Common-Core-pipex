/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:50:46 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/03 18:03:11 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	int	lower_digit;

	lower_digit = c + 32;
	if (lower_digit >= 'a' && lower_digit <= 'z')
		return (lower_digit);
	return (c);
}
