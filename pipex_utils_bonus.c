/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:00:34 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/11 22:45:04 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds(t_cmd *pids_lst)
{
	t_cmd	*curr;

	curr = pids_lst;
	while (curr)
	{
		if (curr->stdin_fd != STDIN_FILENO)
			close(curr->stdin_fd);
		if (curr->stdout_fd != STDOUT_FILENO)
			close(curr->stdout_fd);
		curr = curr->next;
	}
}

char	*get_arg(char **argv, int index)
{
	int	i;

	index = -index;
	i = 0;
	while (argv[i + index])
		i++;
	return (argv[i]);
}

void	send_err(char *pre, char *msg1, char *msg2, int has_perror)
{
	ft_putstr_fd(pre, 2);
	if (msg1)
		ft_putstr_fd(msg1, 2);
	if (msg2)
		ft_putstr_fd(msg2, 2);
	if (has_perror)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
}
