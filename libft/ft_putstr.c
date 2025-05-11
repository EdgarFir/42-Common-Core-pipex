/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:35:54 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/09 23:03:08 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *s)
{
	int	digits;

	digits = 0;
	while (s[digits])
	{
		ft_putchar_fd(s[digits], 1);
		digits++;
	}
	return (digits);
}
