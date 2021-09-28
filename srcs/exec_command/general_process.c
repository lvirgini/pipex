/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/28 15:37:54 by lvirgini         ###   ########.fr       */
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
		{
			if (dup2(cmd->prev->pipe[IN], 0) == -1)
			{
				perror ("dup2");
				exit(EXIT_FAILURE);
			}
		}
		if (cmd->next)
		{
			if (dup2(cmd->pipe[OUT], 1) == -1)
			{
				perror ("dup2");
				exit(EXIT_FAILURE);
			}
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

int	execute_all_cmd(t_cmd *cmd, char *env[])
{
	while (cmd)
	{
		if (cmd->path == NULL)
		{
			write(2, "pipex: ", 8);
			write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
			write(2, ": command not found\n", 20);
		}
		else
		{
			if (cmd->next && pipe(cmd->pipe) == -1)
			{
				perror ("pipe");
				return (FAILURE);
			}
			cmd->pid = creating_process(cmd, env);
			if (cmd->next)
				close(cmd->pipe[OUT]);
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	wait_all_process(t_cmd *cmd)
{
	while (cmd)
	{
		waitpid(cmd->pid, NULL, 0);
		cmd = cmd->next;
	}
}
int	make_pipex(t_cmd *cmd, char *env[], char *input, char *output)
{
	int		std_io[2];

	if (set_up_input(std_io, input) == FAILURE)
	{
		cmd->pipe[IN] = -1;
		cmd = cmd->next;
	}
	if (set_up_output(std_io, output) == FAILURE)
	{
		//close_pipe(std_io);
		return (FAILURE);
	}
	execute_all_cmd(cmd, env);
	wait_all_process(cmd);
	//close_pipe(std_io);
	return (SUCCESS);
}
