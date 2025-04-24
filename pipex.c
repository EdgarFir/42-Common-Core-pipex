#include "pipex.h"

int open_files(int *files_fd, char *argv[])
{
	int input_fd;
	int output_fd;

	input_fd = open(argv[1], O_RDONLY);
	output_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (input_fd < 0)
	{
		perror("input_fd error");
		return (0);
	}
	if (output_fd < 0)
	{
		perror("output_fd error");
		return (0);
	}
	files_fd[0] = input_fd;
	files_fd[1] = output_fd;
	return (1);
}

char	*free_cmd(char *cmd[])
{
	int i;

	if (!(*cmd))
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (NULL);
}

#include <stdio.h>
char *get_path_cmd(char *cmd[])
{
	char *path_cmd;

	if (!cmd || !cmd[0])
		return (NULL);
	path_cmd = ft_strjoin("/bin/", cmd[0]);
	if (!path_cmd)
		return (free_cmd(cmd));
	if (!access(path_cmd, F_OK))
		return (path_cmd);
	printf("%s\n", path_cmd);
	free(path_cmd);
	perror("access path cmd");
	return (NULL);
}

int exec_input_proccess(int *pipe_fd, pid_t input_pid, int input_fd, char *argv[])
{
	char *cmd_path;
	char **cmd;

	input_pid = fork();
	if (input_pid < 0)
	{
		perror("fork input_pid");
		return (0);
	}
	cmd = ft_split(argv[2], ' ');
	cmd_path = get_path_cmd(cmd);
	if (!cmd_path)
		return (0);
	if (input_pid == 0)
	{
		close(pipe_fd[0]);
		dup2(input_fd, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(input_fd);
		close(pipe_fd[1]);
		if (execve(cmd_path, cmd, NULL) < 0)
		{
			free(cmd_path);
			free_cmd(cmd);
			perror("execv input error");
			return (0);
		}
	}
	free(cmd_path);
	free_cmd(cmd);
	return (1);
}

int exec_output_proccess(int *pipe_fd, pid_t output_pid, int output_fd, char *argv[])
{
	char *args[] = {"uniq", NULL};
	
	output_pid = fork();
	if (output_pid < 0)
	{
		perror("fork input_pid");
		return (0);
	}
	if (output_pid == 0)
	{
		close(pipe_fd[1]);
		dup2(output_fd, STDOUT_FILENO);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(output_fd);
		close(pipe_fd[0]);
		if (execve("/bin/uniq", args, NULL) < 0)
		{
			perror("execv output error");
			return (0);
		}
	}
	return (1);
}

void close_descriptors(int *pipe_fd, int *files_pd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	close(files_pd[0]);
	close(files_pd[1]);
}

int	process_sons(int *pipe_fd, pid_t *pids, int *files_fd, char *argv[])
{
	if (exec_input_proccess(pipe_fd, pids[0], files_fd[0], argv) == 0)
		return (0);
	if (exec_output_proccess(pipe_fd, pids[1], files_fd[1], argv) == 0)
		return (0);
	return (1);
}
void process_father(int *pids)
{
	waitpid(pids[0], NULL, 0);
	waitpid(pids[1], NULL, 0);
}

int main(int argc, char *argv[]) 
{
	pid_t pids[2];
	int pipe_fd[2];
	int files_fd[2];

	if (argc == 5)
	{
		if (!open_files(files_fd, argv))
			exit(EXIT_FAILURE);
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		if (process_sons(pipe_fd, pids, files_fd, argv) == 0)
			exit(EXIT_FAILURE);
		close_descriptors(pipe_fd, files_fd);
		process_father(pids);
		return (0);
	}
    return (1);
}
