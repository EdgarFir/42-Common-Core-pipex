/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:33:34 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/05 17:30:09 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void start_pipex(char **argv, int argc, char **envp)
{
	int	*fds_lst;
	pid_t *pds_lst;
	int files_fd[2];
	int fds_total;

	fds_total = (argc - 4) * 2 + 2;
	open_files(files_fd, argv[1], argv[argc - 1]);
	fds_lst = (int *)malloc(sizeof(int) * fds_total);
	build_fds_lst(fds_lst, files_fd, argc);
	pds_lst = (pid_t *)malloc(sizeof(pid_t) * (argc - 3));
	if (!pds_lst)
	{
		free(fds_lst);
		exit(1);
	}
	proccess_sons(pds_lst, fds_lst, argv, envp, argc - 3);
	close_fds(fds_lst, fds_total, -1, 1);
	proccess_father(fds_lst, pds_lst, argc - 3);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
	{
		make_init_checks(argv, argc, envp);
		start_pipex(argv, argc, envp);
	}
	ft_putstr_fd("Invalid number of arguments.\n", 2);
	exit(1);
}
