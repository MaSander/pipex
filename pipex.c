/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msander <msander@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 22:28:20 by msaner-           #+#    #+#             */
/*   Updated: 2023/03/21 23:28:03 by msander          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **g_env;

void	execute(char *argv)
{
	char	*path;
	char	**cmd_arg;

	cmd_arg = ft_split(argv, '|');
	path = find_path(cmd_arg[0], g_env);
	if (!path)
	{
		ft_free_array(cmd_arg);
		invalid_command();
	}
	execve(path, cmd_arg, g_env);
}

void	execute_in(char **argv, int count_cmd, int *pipe_fd)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], 1);
	execute(argv[count_cmd]);
}

void execute_on_pipe(char **argv, int count_cmd, int *pipe_fd)
{
	dup2(pipe_fd[0], 0);
	dup2(pipe_fd[1], 1);
	execute(argv[count_cmd]);
}

void	execute_out(char **argv, int count_cmd, int *pipe_fd)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	dup2(1, 1);
	execute(argv[count_cmd]);
}

int	main(int argc, char *argv[], char **env)
{
	int		pipe_fd[2];
	pid_t	pid;
	int 	count_cmd;

	g_env = env;
	count_cmd = 1;

	while(argc != count_cmd)
	{
		pid = fork();
		if (pid == -1)
			print_error_fd("\033[31mError: Internal Error. fork()\n\e[0m", 1);
		if(pid == 0)
		{
			if (count_cmd == 1)
				execute_in(argv, count_cmd, pipe_fd);
			if (count_cmd + 1 == argc)
				execute_out(argv, count_cmd, pipe_fd);
			else
				execute_on_pipe(argv, count_cmd, pipe_fd);
		}
		else
			waitpid(pid, NULL, 0);
		count_cmd++;
	}
	return (0);
}
