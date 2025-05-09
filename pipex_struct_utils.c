/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 00:25:25 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/09 17:38:33 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_lst_exit(t_cmd **pids_lst, int status)
{
	t_cmd	*temp;
	t_cmd	*curr;
	
	if (!(*pids_lst))
		exit(status) ;
	curr = *pids_lst;
	while (curr)
	{
		temp = curr->next;
		close(curr->stdin_fd);
		close(curr->stdout_fd);
		free(curr);
		curr = temp;
	}
	*pids_lst = NULL;
	exit(status);
}

t_cmd	*create_new_pid(char *cmd, int infile, int outfile, int bef_stdin_fd)
{
	t_cmd	*new;
	int		fd[2];

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->cmd_flags = cmd;
	if (!outfile)
	{
		if (pipe(fd) == -1)
			return (NULL);
		new->stdout_fd = fd[1];
		new->next_stdin_fd = fd[0];
	}
	else
	{
		new->stdout_fd = outfile;
		new->next_stdin_fd = -1;
	}
	if (outfile || (!infile && !outfile))
		new->stdin_fd = bef_stdin_fd;
	else
		new->stdin_fd = infile;
	return (new);
}

void add_back_pids_lst(t_cmd **pids_lst, t_cmd *new)
{
	t_cmd *ptr;

	ptr = *pids_lst;
	if (!(*pids_lst))
		*pids_lst = new;
	else
	{
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = new;
	}
}

t_cmd	**build_pids_lst(t_cmd **pids_lst, char **argv, int argc)
{
	int		i;
	int		files_fd[2];
	t_cmd	*new;
	t_cmd	*curr;

	files_fd[0] = open(argv[1], O_RDONLY);
	files_fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	i = 0;
	while (i < argc - 3)
	{
		if (!i)
			new = create_new_pid(argv[i + 2], files_fd[0], 0, 0);
		else if (i == argc - 4)
			new = create_new_pid(argv[i + 2], 0, files_fd[1], curr->next_stdin_fd);
		else
			new = create_new_pid(argv[i + 2], 0, 0, curr->next_stdin_fd);
		if (!new)
			clean_lst_exit(pids_lst, EXIT_FAILURE); // Exit clean and close
		curr = new;
		add_back_pids_lst(pids_lst, new);
		i++;
	}
	return (pids_lst);
}
