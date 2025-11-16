/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 19:30:25 by edfreder          #+#    #+#             */
/*   Updated: 2025/11/16 17:49:37 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_cmd
{
	int				stdin_fd;
	int				stdout_fd;
	int				next_stdin_fd;
	pid_t			pid;
	char			*cmd_flags;
	struct s_cmd	*next;
}	t_cmd;

# define CMD_ERR ": command not found\n"
# define ENV_ERR ": No such file or directory\n"
# define DUP2_ERR "Error duplicating file descriptor\n"

/* Errors */
int		clean_return_status(char **split1, char **split2, char *s1, int status);
char	*clean_return_str(char **split1, char **split2, char *s1, char *s);
int		valid_file(char **argv, int infile, int outfile);
int		validate_files_cmd(int cmd_i, t_cmd *pid, char *cmd_path, char **argv);
/* Utils */
void	send_err(char *pre, char *msg1, char *msg2, int has_perror);
void	close_fds(t_cmd *pids_lst);
char	*get_arg(char **argv, int index);
/* Path */
char	*get_envp_path(char **envp);
char	*get_cmd_path(t_cmd *pid, char **envp);
/* Struct */
t_cmd	**build_pids_lst(t_cmd **pids_lst, char **argv, int argc, int mode);
void	clean_lst_exit(t_cmd **pids_lst, int status);
/* Processs*/
int		redirect_stdin_stdout(t_cmd *pid);
void	proc_father(t_cmd *pids_lst);
int		proc_son(t_cmd *pids_lst, t_cmd *pid, char **envp, char *cmd_path);
int		exec_cmd(t_cmd *pid, char **envp, char *cmd_path);
/*Parser */
char	**parse_cmds(char *s);
void	*free_split(char **parse_cmds);

#endif