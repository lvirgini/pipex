/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/23 21:29:13 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	creating_process(t_cmd *cmd, int input_fd[2], int output_fd[2],
	char *env[])
{
	pid_t	cpid;

	cpid = fork();
	if (cpid == -1)
	{
		error("fork");
		return (-1);
	}
	if (cpid == 0)
	{
		close (input_fd[1]);
		close(output_fd[0]);
		if (dup2(input_fd[0], 0) == -1 || dup2(output_fd[1], 1) == -1)
			perror("dup2");
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close (input_fd[0]);
		close(output_fd[1]);
	}
	return (cpid);
}

void	copy_pipe_fd(int fd[2], int first, int second)
{
	fd[0] = dup(first);
	fd[1] = dup(second);
}

int	make_pipex(t_cmd *cmd, int nb_cmd, int outfile, char *env[])
{
	int		i;
	int		input_fd[2];
	int		output_fd[2];
	pid_t	pid[2];

	i = 0;
	copy_pipe_fd(input_fd, 0, -1);
	while (i < nb_cmd - 1)
	{
		if (pipe(output_fd) == -1)
		{
			perror("pipe");
			return (FAILURE);
		}
		pid[i] = creating_process(&cmd[i], input_fd, output_fd, env);
		copy_pipe_fd(input_fd, output_fd[0], output_fd[1]);
		i++;
	}
	copy_pipe_fd(output_fd, -1, outfile);
	pid[i] = creating_process(&cmd[i], input_fd, output_fd, env);
	wait(NULL);
	return (SUCCESS);
}
