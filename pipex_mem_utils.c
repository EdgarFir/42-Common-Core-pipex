/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_mem_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:58:43 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/05 17:13:29 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int clean_and_get_error(char **split1, char **split2, char *s1, char *s2, int exit_status)
{
	if (split1)
		clean_split(split1);
	if (split2)
		clean_split(split2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (exit_status);
}

void clean_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void clean_lsts_and_exit(int *lst1, char *lst2, int exit_status)
{
	if (lst1)
		free(lst1);
	if (lst2)
		free(lst2);
	exit(exit_status);
}

void clean_pids_fds_and_exit(int *fds_lst, pid_t *pids_lst, int exit_status)
{
	if (fds_lst)
		free(fds_lst);
	if (pids_lst)
		free(pids_lst);
	exit(exit_status);
}