/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:45:01 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/03 18:02:50 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	int	upper_digit;

	upper_digit = c - 32;
	if (upper_digit >= 'A' && upper_digit <= 'Z')
		return (upper_digit);
	return (c);
}
