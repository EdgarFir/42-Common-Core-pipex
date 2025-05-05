/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 22:25:22 by edfreder          #+#    #+#             */
/*   Updated: 2025/04/09 20:18:33 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*curr;
	t_list	*next;

	if (lst && *lst && del)
	{
		curr = *lst;
		while (curr)
		{
			next = curr->next;
			ft_lstdelone(curr, del);
			curr = next;
		}
		*lst = NULL;
	}
}
