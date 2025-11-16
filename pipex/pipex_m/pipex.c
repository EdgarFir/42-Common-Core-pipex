/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:31:42 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/11 22:43:16 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_pipeline(t_cmd *pids_lst, char **argv, char **envp)
{
	t_cmd	*curr;
	char	*cmd_path;
	int		i;
	int		status;

	curr = pids_lst;
	i = 0;
	while (curr)
	{
		curr->pid = fork();
		if (curr->pid == -1)
			break ;
		if (curr->pid == 0)
		{
			cmd_path = get_cmd_path(curr, envp);
			status = validate_files_cmd(i, curr, cmd_path, argv);
			if (status > 0)
				clean_lst_exit(&pids_lst, status);
			clean_lst_exit(&pids_lst, proc_son(pids_lst, curr, envp, cmd_path));
		}
		curr = curr->next;
		i++;
	}
	proc_father(pids_lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*pids_lst;

	pids_lst = NULL;
	if (argc == 5)
	{
		build_pids_lst(&pids_lst, argv, argc, 1);
		exec_pipeline(pids_lst, argv, envp);
	}
	ft_putstr_fd("Invalid number of arguments!\n", 2);
	exit(1);
}
