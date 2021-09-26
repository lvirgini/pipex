/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/26 23:27:05 by lvirgini         ###   ########.fr       */
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
		if (cmd->prev)
			dup2(cmd->prev->pipe[IN], 0);
		if (cmd->next)
			dup2(cmd->pipe[OUT], 1);
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else
		close(cmd->pipe[OUT]);
	return (pid);
}

int	make_pipex(t_cmd *cmd, char *env[])
{
	pid_t	pid;
	int		status;

	while (cmd)
	{
		if (cmd->next)
			if (pipe(cmd->pipe) == -1)
				return (FAILURE);
		pid = creating_process(cmd, env);
		cmd = cmd->next;
	}
	waitpid(-1, &status, 0);
}
