/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/30 16:28:27 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	test_existing_command(t_cmd *cmd)
{
	if (cmd->path == NULL)
		{
			if (access(cmd->argv[0], X_OK) == 0)
			{
				cmd->path = ft_strdup(cmd->argv[0]);
				return ;
			}
			write(2, "pipex: ", 8);
			if (cmd->argv && cmd->argv[0])
				write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
			write(2, ": command not found\n", 20);
			close(cmd->pipe[OUT]);
			exit(127);
		}
}

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
		test_existing_command(cmd);
		exec_command(cmd, env);
		perror("execve");
		exit(errno);
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
		cmd->pid = creating_process(cmd, env);
		if (cmd->next)
			close(cmd->pipe[OUT]);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

int	wait_all_process(t_cmd *cmd)
{
	int	last_status;

	while (cmd)
	{
		last_status = 0;
		waitpid(cmd->pid, &last_status, 0);
		close_pipe(cmd->pipe);
		cmd = cmd->next;
	}
	if (last_status == 0)
		return (0);
	//dprintf(2, "%d %d\n", last_status,WEXITSTATUS(last_status));
	errno = WEXITSTATUS(last_status);
	return (errno);
}

int	make_pipex(t_cmd *cmd, char *env[])
{
	execute_all_cmd(cmd, env);
	return (wait_all_process(cmd));
}
