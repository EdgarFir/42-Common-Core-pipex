/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proccess_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:44:32 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/07 17:34:35 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	redirect_stdin_stdout(t_cmd *pids_lst, t_cmd *pid)
{
	if (dup2(pid->stdin_fd, STDIN_FILENO) == -1)
		clean_lst_exit(&pids_lst, 1); // Exit clean and close
	if (dup2(pid->stdout_fd, STDOUT_FILENO) == -1)
		clean_lst_exit(&pids_lst, 1); // " "
	//clean_lst_exit(&pids_lst, 1);
	
}

void exec_cmd(t_cmd *pids_lst, t_cmd *pid, char **envp)
{
	char **cmd_split;
	char *cmd_path;

	cmd_split = parse_cmds(pid->cmd_flags);
	if (!cmd_split)
		clean_lst_exit(&pids_lst, EXIT_FAILURE);
	if (access(cmd_split[0], F_OK | X_OK) == 0)
	{
		cmd_path = ft_strdup(cmd_split[0]);
		if (!cmd_path)
			full_clean(pids_lst, cmd_split, NULL, EXIT_FAILURE);
	}
	else
	{
		cmd_path = check_cmd_path(pids_lst, cmd_split, envp);
		if (!cmd_path)
		{
			return;
		}
	}
	if (execve(cmd_path, cmd_split, envp) == -1)
		full_clean(pids_lst, cmd_split, cmd_path, EXIT_FAILURE);
	check_free_helper(NULL, cmd_split, NULL, cmd_path);
}

void proccess_son(t_cmd *pids_lst, t_cmd *pid, char **envp)
{
	int code = 0;
	redirect_stdin_stdout(pids_lst, pid);
	close_fds(pids_lst);
	exec_cmd(pids_lst, pid, envp);
	ft_putstr_fd("redirect", 2);
	//exit(0);
}

void proccess_father(t_cmd *pids_lst)
{
	t_cmd	*curr;
	int		status;
	int		exit_code;

	close_fds(pids_lst);
	curr = pids_lst;
	exit_code = 0;
	while (curr)
	{
		waitpid(curr->pid, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		curr = curr->next;
	}
	clean_lst_exit(&pids_lst, exit_code);
}

