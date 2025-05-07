/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:31:42 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/07 17:35:07 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_pipeline(int argc, char **argv, char **envp)
{
	t_cmd	*pids_lst;
	t_cmd	*curr;
	int		critical_err;

	pids_lst = NULL;
	build_pids_lst(&pids_lst, argv, argc);
	curr = pids_lst;
	critical_err = 0;
	while (curr)
	{
		curr->pid = fork();
		if (curr->pid == -1)
		{
			critical_err = 1;
			break ;
		}
		if (curr->pid == 0)
		{
			proccess_son(pids_lst, curr, envp);
		}
		curr = curr->next;
	}
	if (critical_err)
		clean_lst_exit(&pids_lst, EXIT_FAILURE); // Clean lst.
	proccess_father(pids_lst);
}

int	main(int argc, char **argv, char **envp)
{
	char	*envp_path;

	if (argc >= 5)
	{
		envp_path = check_envp_path(envp);
		if (!envp_path)
		{
			ft_putstr_fd("No environment variables.\n", 2);
			exit(1);
		}
		/*
		if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1] == 8))
		{
			// Here doc
		}
		*/
		// Start pipex
		exec_pipeline(argc, argv, envp);
	}
	ft_putstr_fd("Invalid number of arguments!\n", 2);
	exit(1);
}
