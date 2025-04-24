/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:25:56 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/08 23:09:51 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(int n)
{
	size_t	digits;

	digits = 0;
	if (n < 0)
		digits++;
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

static void	ft_format_int(char *nbr, long n, int start, int end)
{
	int	end_temp;

	end_temp = end;
	while (start <= end)
	{
		nbr[end] = '0' + (n % 10);
		n /= 10;
		end--;
	}
	nbr[end_temp + 1] = '\0';
}

char	*ft_itoa(int n)
{
	size_t	digits;
	char	*nbr;
	long	n_long;

	if (!n)
	{
		nbr = ft_strdup("0");
		if (!nbr)
			return (NULL);
		return (nbr);
	}
	n_long = n;
	digits = ft_nbrlen(n_long);
	nbr = ft_calloc(digits + 1, sizeof(char));
	if (!nbr)
		return (NULL);
	if (n_long < 0)
	{
		nbr[0] = '-';
		ft_format_int(nbr, n_long * -1, 1, digits - 1);
	}
	else
		ft_format_int(nbr, n_long, 0, digits - 1);
	return (nbr);
}
