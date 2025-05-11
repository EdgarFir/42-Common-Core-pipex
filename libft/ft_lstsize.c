/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:23:21 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/10 01:43:45 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*curr;

	size = 0;
	if (!lst)
		return (0);
	curr = lst;
	while (curr)
	{
		curr = curr->next;
		size++;
	}
	return (size);
}
