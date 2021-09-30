/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/30 20:58:39 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** check if commande can be execute by execve
**	if cmd->path exist : access found the executable.
**	if cmd->path doesn't exist : access not found the executable with env
**	make errno to 127 : command not found
*/

int	is_command_executable(t_cmd *cmd)
{
	if (cmd->path == NULL)
	{
		write(2, "pipex: ", 8);
		if (cmd->argv && cmd->argv[0])
			write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
		write(2, ": command not found\n", 20);
		close(cmd->pipe[OUT]);
		errno = 127;
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
** create a child processus with fork()
** in CHILD : 
**		setup the intput/output
**		check if command is executable by execve
**		execute command
** in PARENT : 
**		return child pid;
*/

pid_t	create_child_process(t_cmd *cmd, char *env[])
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
		if (set_up_io_in_fork(cmd) == FAILURE)
			exit(free_and_return(cmd));
		if (is_command_executable(cmd) == FAILURE)
			exit(free_and_return(cmd));
		execve_this_command(cmd, env);
		free_and_return(cmd);
		exit(errno);
	}
	return (pid);
}

void	close_pipe(int pipe[2])
{
	close(pipe[IN]);
	close(pipe[OUT]);
}

/*
** PARENT : wait all processus terminated
**	make errno of PARENT like the last child processus.
** 	return status of last command.
*/

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
	/*(void)cmd;
	waitpid(-1, &last_status, WUNTRACED);*/
	errno = WEXITSTATUS(last_status);
	return (last_status);
	//if (last_status == 0)
	//	return (0);
	//dprintf(2, "%d %d\n", last_status,WEXITSTATUS(last_status));
	return (errno);
}

/*
** 	for pipex : while command next exist, create a pipe between them
** 	create the child processus and keep the pid.
**	close pipe[OUT] not used in PARENT.
*/

int	exec_all_commands(t_cmd *cmd, char *env[])
{
	while (cmd)
	{
		if (cmd->next && pipe(cmd->pipe) == -1)
		{
			perror ("pipe");
			return (FAILURE);
		}
		cmd->pid = create_child_process(cmd, env);
		if (cmd->next)
			close(cmd->pipe[OUT]);
		cmd = cmd->next;
	}
	return (wait_all_process(cmd));
}
