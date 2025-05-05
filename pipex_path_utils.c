/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:42:18 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/05 15:47:30 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char *cmd, char **envp)
{
	char	*envp_path;
	char	**envp_path_dirs;
	char	*cmd_dir;
	char	*cmd_path;
	int		i;

	envp_path = get_envp_path(envp);
	envp_path_dirs = ft_split(envp_path + 5, ':');
	cmd_dir = ft_strjoin("/", cmd);
	i = 0;
	while (envp_path_dirs[i])
	{
		cmd_path = ft_strjoin(envp_path_dirs[i], cmd_dir);
		if (access(cmd_path, F_OK || X_OK) == 0)
		{
			free(cmd_dir);
			clean_split(envp_path_dirs);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(cmd_dir);
	clean_split(envp_path_dirs);
	return (NULL);
}

char	*get_envp_path(char **envp)
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