/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:18:45 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/12 00:34:24 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*build_line(t_list *lst)
{
	char	*line;
	t_list	*curr;
	int		i;

	line = ft_calloc(ft_lstsize(lst) + 1, sizeof(char));
	if (!line)
	{
		ft_lstclear(&lst, &free);
		exit(1);
	}
	curr = lst;
	i = 0;
	while (curr)
	{
		ft_memcpy(&line[i], curr->content, 1);
		i++;
		curr = curr->next;
	}
	return (line);
}

void	read_and_build_line(t_list **lst, int fd)
{
	char	buffer[1];
	t_list	*new;

	while (read(fd, buffer, 1))
	{
		if (!ft_memcmp("\n", buffer, 1))
			break ;
		new = ft_lstnew(ft_strdup(buffer));
		if (!new)
		{
			ft_lstclear(lst, &free);
			exit(1);
		}
		ft_lstadd_back(lst, new);
		buffer[0] = '\0';
	}
}

void	write_temp_file(int fd, int temp_fd, char *limiter)
{
	char	*line;
	t_list	*lst;

	while (1)
	{
		lst = NULL;
		ft_putstr_fd("> ", 1);
		read_and_build_line(&lst, fd);
		line = build_line(lst);
		if (!ft_strcmp(line, limiter))
		{
			free(line);
			ft_lstclear(&lst, &free);
			return ;
		}
		ft_putendl_fd(line, temp_fd);
		ft_lstclear(&lst, &free);
		free(line);
	}
}
