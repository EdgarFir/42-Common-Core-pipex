/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_shell_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:16:57 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/12 01:59:55 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	count_cmds(char *s)
{
	int		i;
	char	delimiter;
	int		cmds;

	i = 0;
	cmds = 0;
	while (s[i])
	{
		delimiter = ' ';
		while (s[i] && s[i] == delimiter)
			i++;
		if (s[i])
		{
			if (s[i] == '\'' || s[i] == '"')
				delimiter = s[i];
			cmds++;
			i++;
		}
		while (s[i] && s[i] != delimiter)
			i++;
		if (delimiter != ' ')
			i++;
	}
	return (cmds);
}

char	*split_cmd(char *s, int start, char delimiter)
{
	size_t	len;

	len = 0;
	while (s[start + len] && s[start + len] != delimiter)
		len++;
	return (ft_substr(s, start, len));
}

void	*free_split(char **parse_cmds)
{
	int	i;

	i = 0;
	while (parse_cmds[i])
	{
		free(parse_cmds[i]);
		i++;
	}
	free(parse_cmds);
	return (NULL);
}

char	**build(char **parsed_cmds, char *s, int cmds)
{
	int		i;
	int		j;
	char	delimiter;

	i = 0;
	j = 0;
	while (i < cmds)
	{
		delimiter = ' ';
		while (s[j] && s[j] == delimiter)
			j++;
		if (s[j] == '\'' || s[j] == '"')
		{
			delimiter = s[j];
			j++;
		}
		parsed_cmds[i] = split_cmd(s, j, delimiter);
		if (!parsed_cmds[i])
			return (free_split(parsed_cmds));
		j += ft_strlen(parsed_cmds[i]) + 1;
		i++;
	}
	return (parsed_cmds);
}

char	**parse_cmds(char *s)
{
	char	**parsed_cmds;
	int		cmds;

	if (!s)
		return (NULL);
	cmds = count_cmds(s);
	parsed_cmds = (char **)malloc(sizeof(char *) * (cmds + 1));
	if (!parsed_cmds)
		return (NULL);
	parsed_cmds[cmds] = NULL;
	if (!build(parsed_cmds, s, cmds))
		return (NULL);
	return (parsed_cmds);
}
