/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:42:23 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/09 17:48:39 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int valid_cmd(int cmd_index, char *cmd_path, char **argv)
{
	if (!ft_memcmp("command not found.", cmd_path, ft_strlen(cmd_path)))
			return (send_custom_error(argv[cmd_index + 2], ": command not found\n", NULL, 0, 0));
	else if (!ft_memcmp("no envp.", cmd_path, ft_strlen(cmd_path)))
		return (send_custom_error("sh: ", argv[cmd_index + 2], ": No such file or directory\n", 0, 0));
	return (1);
}
int	validate_files_and_cmd(int cmd_index, t_cmd *pid, char *cmd_path, char **argv)
{
	if (!cmd_path)
		return (1);
	if (cmd_index == 0)
	{
		if (!valid_file(argv, 1, 0))
			return (clean_and_return_status(NULL, NULL, cmd_path, 1));
		if (!valid_cmd(cmd_index, cmd_path, argv))
			return (clean_and_return_status(NULL, NULL, cmd_path, 127));
	}
	else if (pid->next == NULL)
	{
		if (!valid_cmd(cmd_index, cmd_path, argv))
			return (clean_and_return_status(NULL, NULL, cmd_path, 127));
		if (!valid_file(argv, 0, 1))
			return (clean_and_return_status(NULL, NULL, cmd_path, 1));
	}
	else
	{
		if (!valid_cmd(cmd_index, cmd_path, argv))
			return (clean_and_return_status(NULL, NULL, cmd_path, 127));
	}
	return (0);
}

int valid_file(char **argv, int infile, int outfile)
{
	if (infile)
	{
		if (access(argv[1], R_OK) == -1)
			return(send_custom_error("sh: ", argv[1], NULL, 1, 0));
	}
	else if (outfile)
	{
		if (access(get_arg(argv, -1), W_OK) == -1)
			return(send_custom_error("sh: ", get_arg(argv, -1), NULL, 1, 0));
	}
	return (1);
}

int	clean_and_return_status(char **split1, char **split2, char *s1, int status)
{
	if (s1)
		free(s1);
	if (split1)
		free_split(split1);
	if (split2)
		free_split(split2);
	return (status);
}

char	*clean_and_return_str(char **split1, char **split2, char *s1, char *str)
{
	if (s1)
		free(s1);
	if (split1)
		free_split(split1);
	if (split2)
		free_split(split2);
	return (str);
}
