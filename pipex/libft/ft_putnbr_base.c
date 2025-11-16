/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:33:41 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/04 23:07:56 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(unsigned long long n, char *base_s, int base_i)
{
	int	total;

	total = 0;
	if (n >= (unsigned long long)base_i)
		total += ft_putnbr_base(n / base_i, base_s, base_i);
	ft_putchar_fd(base_s[n % base_i], 1);
	return (total + 1);
}
