/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:28:48 by edfreder          #+#    #+#             */
/*   Updated: 2025/05/05 17:29:56 by edfreder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft/libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

// Checks
void	make_init_checks(char **argv, int argc, char **envp);
void	check_files(char *infile, char *outfile);
void	check_env_path(char **envp);
int		clean_quotes(char **split);

// Path
char	*get_envp_path(char **envp);
char	*get_cmd_path(char *cmd, char **envp);

// Fds 
void	build_fds_lst(int *fds_lst, int *files_fd, int argc);
void	open_files(int *files_fd, char *infile, char *outfile);
int		build_pipes(int *fd_list, int pipes_count);
int		add_pipe(int *fd_list, int fd_list_ind);
void	close_fds(int *fds_lst, int fds_total, int pid_index, int all);


// Processes
int		proccess_sons(pid_t *pids, int *fd_list, char **argv, char **envp, int cmds_count);
void	redirect_stdin_stdout(int ft_stdin, int ft_stdout);
void	proccess_father(int *fd_lst, pid_t *pids, int pids_size);
int		exec_cmd(char *cmd_flags, char **envp);

// Mem
void	clean_lsts_and_exit(int *lst1, char *lst2, int exit_status);
void	clean_split(char **split);
void 	clean_pids_fds_and_exit(int *fds_lst, pid_t *pids_lst, int exit_status);
int 	clean_and_get_error(char **split1, char **split2, char *s1, char *s2, int exit_status);


#endif