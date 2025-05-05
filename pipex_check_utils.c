/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:36:12 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/05 14:16:56 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	clean_quotes(char **split)
{
	int		i;
	size_t len;
	char	*trimm;
	
	i = 0;
	while (split[i])
	{
		len = ft_strlen(split[i]);
		if (len >= 2)
		{
			trimm = ft_strtrim(split[i], "\"'");
			if (!trimm)
				return (0);
			free(split[i]);
			split[i] = trimm;
		}
		i++;
	}
	return (1);
}

void check_env_path(char **envp)
{
	if (!get_envp_path(envp))
	{
		perror("No environment variables detected.\n");
		exit(1);
	}
}

void check_files(char *infile, char *outfile)
{
	if (access(infile, F_OK | R_OK) == -1)
	{
		perror(infile);
		exit(1);
	}
	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
		{
			perror(outfile);
			exit(1);
		}
	}
}

void make_init_checks(char **argv, int argc, char **envp)
{
	check_env_path(envp);
	check_files(argv[1], argv[argc - 1]);
}