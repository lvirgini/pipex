/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/27 18:25:03 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	creating_process(t_cmd *cmd, char *env[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{
		if (cmd->prev && cmd->prev->pipe[IN] != -1)
			dup2(cmd->prev->pipe[IN], 0);
		if (cmd->next)
		{
			dup2(cmd->pipe[OUT], 1);
			close(cmd->pipe[IN]);
		}
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

void	close_pipe(int	pipe[2])
{
	close(pipe[IN]);
	close(pipe[OUT]);
}


int	make_pipex(t_cmd *cmd, char *env[], char *input, char *output)
{
	int		status;
	pid_t	pid;
	int		std_io[2];

	if (set_up_input(std_io, input) == FAILURE)
	{
		cmd->pipe[IN] = -1;
		cmd = cmd->next;
	}	
	if (set_up_output(std_io, output) == FAILURE)
	{
		close_pipe(std_io);
		return (FAILURE);
	}
	while (cmd)
	{
		if (cmd->next)
			if (pipe(cmd->pipe) == -1)
				return (FAILURE);
		pid = creating_process(cmd, env);
		if (cmd->next)
			close(cmd->pipe[IN]);
		cmd = cmd->next;
	}
	waitpid(-1, &status, 0);
	close_pipe(std_io);
	return (SUCCESS);
}
