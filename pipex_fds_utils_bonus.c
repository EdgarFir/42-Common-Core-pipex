/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_fds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:27:47 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/04 23:01:51 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_fds(int *fds_lst, int fds_total, int pid_index, int all)
{
	int start;
	int end;

	if (all)
	{
		start = 0;
		end = fds_total - 1;
	}
	else
	{
		start = 1;
		end = fds_total - 2;
		if (!pid_index)
			start--;
		else if (pid_index  == fds_total - 1)
			end++;
	}
	while (start <= end)
	{
		close(fds_lst[start]);
		start++;
	}
}

int add_pipe(int *fd_list, int fd_list_ind)
{
	int fd[2];

	if (pipe(fd) == -1)
		return (0);
	fd_list[fd_list_ind] = fd[1]; // Pronto, aqui associo logo, pela ordem que te mostrei ao bocado
	fd_list[fd_list_ind + 1] = fd[0];
	return (1);
}

int build_pipes(int *fd_list, int pipes_count)
{
	int i;
	int j;
	
	i = 0;
	j = 1;
	while (i < pipes_count)
	{
		if (!add_pipe(fd_list, j))
		{
			free(fd_list);
			exit(1);
		}
		i++;
		j += 2;
	}
	return (1);
}

void open_files(int *files_fd, char *infile, char *outfile)
{
	files_fd[0] = open(infile, O_RDONLY);
	if (files_fd[0] == -1)
	{
		perror(infile);
		exit(1);
	}
	files_fd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files_fd[1] == -1)
	{
		perror(outfile);
		exit(1);
	}
}

void build_fds_lst(int *fds_lst, int *files_fd, int argc)
{
	int fds_total;

	if (!fds_lst)
		exit(1);
	fds_total = (argc - 4) * 2 + 2;
	fds_lst[0] = files_fd[0];
	fds_lst[fds_total - 1] = files_fd[1];
	build_pipes(fds_lst, argc - 4);
}
