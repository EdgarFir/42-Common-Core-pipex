/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proccess_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:53:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/05 17:31:33 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int exec_cmd(char *cmd_flags, char **envp) // Aqui falta me as tais verificacoes
{
	char **cmd_flags_split;
	char *cmd_path;

	cmd_flags_split = ft_split(cmd_flags, ' ');
	if (!cmd_flags_split)
		return (1);
	if (!clean_quotes(cmd_flags_split))
		return (clean_and_get_error(cmd_flags_split, 0, 0, 0, 1));
	cmd_path = get_cmd_path(cmd_flags_split[0], envp);
	if (!cmd_path)
	{
		perror(cmd_flags_split[0]);
		return (clean_and_get_error(cmd_flags_split, 0, 0, 0, 127));
	}
	if (cmd_flags_split[0][0] != '/')
	{
		cmd_path = get_cmd_path(cmd_flags_split[0], envp);
		if (!cmd_path)
		{
			perror(cmd_flags_split[0]);
			return (clean_and_get_error(cmd_flags_split, 0, 0, 0, 127));
		}
	}
	else
		cmd_path = ft_strdup(cmd_flags_split[0]);
	if (execve(cmd_path, cmd_flags_split, envp) == -1)
	{
		perror(cmd_flags_split[0]);
		return (clean_and_get_error(cmd_flags_split, 0, cmd_path, 0, EXIT_FAILURE));
	}
	return (clean_and_get_error(cmd_flags_split, 0, cmd_path, 0, 0));
}

void redirect_stdin_stdout(int ft_stdin, int ft_stdout)
{
	dup2(ft_stdin, STDIN_FILENO);
	dup2(ft_stdout, STDOUT_FILENO);
}

void proccess_father(int *fds_lst, pid_t *pids_lst, int pids_size)
{
	int i = 0;
	int status;
	int	exit_code;

	while (i < pids_size)
	{
		waitpid(pids_lst[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		i++;
	}
	clean_pids_fds_and_exit(fds_lst, pids_lst, exit_code);
}

int proccess_sons(pid_t *pids, int *fd_list, char **argv, char **envp, int pids_count)
{
	int i;
	int j;
	int fds_count;
	int code;

	i = 0;
	j = 0;
	fds_count = ((pids_count - 1) * 2) + 2;
	while (i < pids_count)
	{
		pids[i] = fork();
		if (!pids[i])
		{
			redirect_stdin_stdout(fd_list[j], fd_list[j + 1]);
			close_fds(fd_list, fds_count, i, 0);
			code = exec_cmd(argv[i + 2], envp);
			if (code != 0)
				clean_pids_fds_and_exit(fd_list, pids, code);
		}
		i++;
		j += 2;
	}
	return (1);
}
