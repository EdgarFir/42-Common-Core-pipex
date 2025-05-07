/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:38:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/07 17:26:59 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_envp_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5))
			return (envp[i]);
		i++;
	}
	return (NULL);
}

void *check_free_helper(t_cmd *pids_lst, char **split1, char **split2, char *s1)
{	
	if (*split1)
		free_split(split1);
	if (*split2)
		free_split(split2);
	if (s1)
		free(s1);
	// if (pids_lst)
	// 	clean_lst_exit(&pids_lst, EXIT_FAILURE);
}

char *get_path(char **split_path, char *cmd_dir, char **cmd_split, t_cmd *pds_lst)
{
	int	i;
	char *path;

	i = 0;
	while (split_path[i])
	{
		path = ft_strjoin(split_path[i], cmd_dir);
		if (!path)
			check_free_helper(pds_lst, cmd_split, split_path, cmd_dir);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		i++;
		free(path);
	}
	//ft_putstr_fd("No path", 2);
	return (NULL);
}

char	*check_cmd_path(t_cmd *pds_lst, char **cmd_split, char **envp)
{
	char	**split_path;
	char	*cmd_dir;
	char	*path;

	split_path = ft_split(check_envp_path(envp), ':');
	// if (!split_path)
	// 	check_free_helper(pds_lst, cmd_split, NULL, NULL);
	cmd_dir = ft_strjoin("/", cmd_split[0]);
	// if (!cmd_dir)
	// 	check_free_helper(pds_lst, split_path, cmd_split, NULL);
	path = get_path(split_path, cmd_dir, cmd_split, pds_lst);
	if (!path)
	{
		//ft_putstr_fd("Deu merda", 2);
		//check_free_helper(NULL, NULL, NULL, NULL);
		//perror("deu merda");
		//free_split(cmd_split);
		//free(cmd_dir);
		return (NULL);
	}
	return (path);
}

