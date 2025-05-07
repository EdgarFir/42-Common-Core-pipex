/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:42:23 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/07 15:49:04 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_fds(t_cmd *pids_lst)
{
	t_cmd *curr = pids_lst;

	while (curr)
	{
		if (curr->stdin_fd != STDIN_FILENO)
			close(curr->stdin_fd);
		if (curr->stdout_fd != STDOUT_FILENO)
			close(curr->stdout_fd);
		curr = curr->next;
	}
}

void	validate_files(char *infile, char *outfile, int *files_fd)
{
	int files1;
	int	files2;
	int has_error;

	has_error = 0;
	files1 = open(infile, O_RDONLY);
	if (files1 == -1)
	{
		send_custom_error(infile);
		has_error = 1;
	}
	files2 = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files2 == -1)
	{
		send_custom_error(outfile);
		has_error = 1;
	}
	if (has_error)
		exit(1);
	files_fd[0] = files1;
	files_fd[1] = files2;
}

void send_custom_error(char *error)
{
	ft_putstr_fd("sh: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(": ", 2);
	perror("");
}

void full_clean(t_cmd *pids_lst, char **split1, char *s1, int status)
{
	if (split1)
		free_split(split1);
	if (s1)
		free(s1);
	if (pids_lst)
		clean_lst_exit(&pids_lst, status);
}
