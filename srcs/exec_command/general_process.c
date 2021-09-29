/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/29 17:27:17 by lvirgini         ###   ########.fr       */
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
		set_up_io_in_fork(cmd);
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	return (pid);
}

void	close_pipe(int pipe[2])
{
	close(pipe[IN]);
	close(pipe[OUT]);
}

int	execute_all_cmd(t_cmd *cmd, char *env[])
{
	while (cmd)
	{
		if (cmd->next && pipe(cmd->pipe) == -1)
		{
			perror ("pipe");
			return (FAILURE);
		}
		if (cmd->path == NULL)
		{
			write(2, "pipex: ", 8);
			if (cmd->argv && cmd->argv[0])
				write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
			write(2, ": command not found\n", 20);
			close(cmd->pipe[OUT]);
		}
		else
		{
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

int	make_pipex(t_cmd *cmd, char *env[])
{
	execute_all_cmd(cmd, env);
	wait_all_process(cmd);
	return (SUCCESS);
}
