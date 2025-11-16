/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:31:42 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/12 11:26:36 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exec_pipeline(t_cmd *pids_lst, char **argv, char **envp, int here_doc)
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
	proc_father(pids_lst, here_doc);
}

void	here_doc(char **argv, char **envp)
{
	int		temp_fd;
	char	*arg[6];
	t_cmd	*lst;

	temp_fd = open("here_doc_temp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (temp_fd == -1)
		exit(1);
	write_temp_file(0, temp_fd, argv[2]);
	close(temp_fd);
	arg[0] = argv[0];
	arg[1] = "here_doc_temp";
	arg[2] = argv[3];
	arg[3] = argv[4];
	arg[4] = argv[5];
	arg[5] = NULL;
	lst = NULL;
	build_pids_lst(&lst, arg, 5, 2);
	exec_pipeline(lst, arg, envp, 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	*pids_lst;

	pids_lst = NULL;
	if (argc >= 5)
	{
		if (!ft_strcmp("here_doc", argv[1]) && argc == 6)
			here_doc(argv, envp);
		build_pids_lst(&pids_lst, argv, argc, 1);
		exec_pipeline(pids_lst, argv, envp, 0);
	}
	ft_putstr_fd("Invalid number of arguments!\n", 2);
	exit(1);
}
