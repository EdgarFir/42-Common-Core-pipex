/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:38:50 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/09 17:23:11 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char *get_path(char *cmd_dir, char **envp)
{
	int		i;
	char	*path;
	char	**path_split;
	char	*envp_path;

	envp_path = get_envp_path(envp);
	if (!envp_path)
		return (ft_strdup("no envp."));
	i = 0;
	path_split = ft_split(envp_path, ':');
	if (!path_split)
		return (NULL);
	while (path_split[i])
	{
		path = ft_strjoin(path_split[i], cmd_dir);
		if (!path)
			return(clean_and_return_str(NULL, path_split, NULL, NULL));
		if (access(path, X_OK) == 0)
			return (clean_and_return_str(NULL, path_split, NULL, path));
		i++;
		free(path);
	}
	return (clean_and_return_str(NULL, path_split, NULL, ft_strdup("command not found")));
}

char *get_cmd_path(t_cmd *pid, char **envp)
{
	char	*cmd_dir;
	char	*path;
	char	**cmd_split;

	cmd_split = NULL;
	cmd_split = parse_cmds(pid->cmd_flags);
	if (!cmd_split)
		return (NULL);
	cmd_dir = ft_strjoin("/", cmd_split[0]);
	if (!cmd_dir)
		return(clean_and_return_str(cmd_split, NULL, cmd_dir, NULL));
	path = get_path(cmd_dir, envp);
	clean_and_return_status(cmd_split, NULL, cmd_dir, 0);
	if (!path)
		return (NULL);
	return (path);
}

