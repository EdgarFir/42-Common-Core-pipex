/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 15:12:55 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/24 00:32:15 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format_p(void *p)
{
	long long	adr;

	if (!p)
		return (ft_putstr("(nil)"));
	adr = (unsigned long long)p;
	return (ft_putstr("0x") + ft_putnbr_base(adr, "0123456789abcdef", 16));
}
