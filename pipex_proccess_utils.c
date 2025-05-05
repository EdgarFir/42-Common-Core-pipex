/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_proccess_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:53:27 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/05 00:55:35 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void build_execve_args(char **execve_args, char *cmd_path, char *cmd_flags)
{
	if (!execve_args)
		return ;
	execve_args[0] = cmd_path;
	execve_args[1] = "-c";
	execve_args[2] = cmd_flags;
	execve_args[3] = NULL; 
}

int exec_cmd(char *cmd_flags, char **envp) // Aqui falta me as tais verificacoes
{
	char **cmd_flags_split;
	char *cmd_path;
	char *execve_args[4];

	cmd_flags_split = ft_split(cmd_flags, ' ');
	if (!cmd_flags_split)
		return (1);
	cmd_path = get_cmd_path("sh", envp);
	if (!cmd_path)
	{
		perror("");
		return (clean_and_get_error(cmd_flags_split, 0, 0, 0, 127));
	}
	build_execve_args(execve_args, cmd_path, cmd_flags);
	if (execve(cmd_path, execve_args, envp) < 0)
	{
		perror(cmd_flags_split[0]);
		return (clean_and_get_error(cmd_flags_split, 0, cmd_path, 0, EXIT_FAILURE));
	}
	clean_and_get_error(cmd_flags_split, 0, cmd_path, 0, 0);
	return (0);
}

void redirect_stdin_stdout(int ft_stdin, int ft_stdout)
{
	dup2(ft_stdin, STDIN_FILENO);
	dup2(ft_stdout, STDOUT_FILENO);
}

void proccess_father(pid_t *pids, int pids_size)
{
	int i = 0;
	while (i < pids_size)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
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
