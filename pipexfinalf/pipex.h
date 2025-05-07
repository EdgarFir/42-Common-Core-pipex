/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:30:25 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/07 16:58:29 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef	struct	s_cmd
{
	int		stdin_fd;
	int		stdout_fd;
	int		next_stdin_fd;
	pid_t	pid;
	char	*cmd_flags;
	struct s_cmd *next;
}	t_cmd;


// Errors
void 	send_custom_error(char *error);
void	validate_files(char *infile, char *outfile, int *files_fd);
void	clean_lst_exit(t_cmd **pids_lst, int status);
void	full_clean(t_cmd *pids_lst, char **split1, char *s1, int status);

// Checks
char	*check_envp_path(char **envp);
char	*check_cmd_path(t_cmd *pds_lst, char **cmd_split, char **envp);
void	*check_free_helper(t_cmd *pids_lst, char **split1, char **split2, char *s1);


// Struct
t_cmd	**build_pids_lst(t_cmd **pids_lst, char **argv, int argc);
void 	add_back_pids_lst(t_cmd **pids_lst, t_cmd *new);
t_cmd	*create_new_pid(char *cmd, int infile, int outfile, int bef_stdin_fd);

// Processs
void	close_fds(t_cmd *pids_lst);
void	redirect_stdin_stdout(t_cmd *pids_lst, t_cmd *pid);
void	proccess_father(t_cmd *pids_lst);
void	proccess_son(t_cmd *pids_lst, t_cmd *pid, char **envp);
void	exec_cmd(t_cmd *pids_lst, t_cmd *pid, char **envp);

// Parser
int		count_cmds(char *s);
char	*split_cmd(char *s, int start, char delimiter);
void	*free_split(char **parse_cmds);
char	**build(char **parsed_cmds, char *s, int cmds);
char	**parse_cmds(char *s);

#endif