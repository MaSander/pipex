/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaner- <msander-@student.42sp.org.br>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:28:20 by msaner-           #+#    #+#             */
/*   Updated: 2022/11/27 07:10:18 by msaner-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *argv, char **env)
{
	char	*path;
	char	**cmd_arg;

	cmd_arg = ft_split_ignore(argv, ' ', '\'');
	path = find_path(cmd_arg[0], env);
	if (!path)
	{
		ft_free_array(cmd_arg);
		invalid_command();
	}
	execve(path, cmd_arg, env);
}

void	execute_in(char **argv, int *pipe_fd, char **env)
{
	int	fd_file_in;

	close(pipe_fd[0]);
	fd_file_in = open(argv[1], O_RDONLY);
	if (fd_file_in == -1)
		exit(0);
	dup2(fd_file_in, 0);
	dup2(pipe_fd[1], 1);
	execute(argv[2], env);
}

void	execute_out(char **argv, int *pipe_fd, char **env)
{
	int	fd_file_out;

	close(pipe_fd[1]);
	fd_file_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 00664);
	if (fd_file_out == -1)
		exit (1);
	dup2(fd_file_out, 1);
	dup2(pipe_fd[0], 0);
	execute(argv[3], env);
}

int	main(int argc, char *argv[], char **env)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5)
		print_error_fd("\033[31mError: Bad arguments\n\e[0m", 1);
	if (pipe(pipe_fd) == -1)
		print_error_fd("\033[31mError: Internal Error. pipe()\n\e[0m", 1);
	pid = fork();
	if (pid == -1)
		print_error_fd("\033[31mError: Internal Error. fork()\n\e[0m", 1);
	if (pid == 0)
		execute_in(argv, pipe_fd, env);
	else
	{
		waitpid(pid, NULL, 0);
		execute_out(argv, pipe_fd, env);
	}
	return (0);
}
