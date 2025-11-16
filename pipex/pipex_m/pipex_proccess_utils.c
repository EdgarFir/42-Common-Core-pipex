/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proccess_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:44:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/11 22:43:37 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_stdin_stdout(t_cmd *pid)
{
	if (dup2(pid->stdin_fd, STDIN_FILENO) == -1)
	{
		send_err("sh: ", DUP2_ERR, NULL, 0);
		return (1);
	}
	if (dup2(pid->stdout_fd, STDOUT_FILENO) == -1)
	{
		send_err("sh: ", DUP2_ERR, NULL, 0);
		return (1);
	}
	return (0);
}

int	exec_cmd(t_cmd *pid, char **envp, char *cmd_path)
{
	char	**cmd_split;

	cmd_split = NULL;
	cmd_split = parse_cmds(pid->cmd_flags);
	if (!cmd_split)
		return (1);
	if (execve(cmd_path, cmd_split, envp) == -1)
		return (clean_return_status(cmd_split, NULL, NULL, 1));
	return (clean_return_status(cmd_split, NULL, cmd_path, 0));
}

int	proc_son(t_cmd *pids_lst, t_cmd *pid, char **envp, char *cmd_path)
{
	int	status;

	status = redirect_stdin_stdout(pid);
	if (status > 0)
		return (clean_return_status(NULL, NULL, cmd_path, 1));
	close_fds(pids_lst);
	status = exec_cmd(pid, envp, cmd_path);
	if (status > 0)
		return (clean_return_status(NULL, NULL, cmd_path, status));
	return (0);
}

void	proc_father(t_cmd *pids_lst)
{
	t_cmd	*curr;
	int		status;
	int		exit_code;

	curr = pids_lst;
	exit_code = 0;
	status = 0;
	close_fds(pids_lst);
	while (curr)
	{
		if (curr->pid == -1)
		{
			perror("fork");
			clean_lst_exit(&pids_lst, 1);
		}
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		curr = curr->next;
	}
	clean_lst_exit(&pids_lst, exit_code);
}
