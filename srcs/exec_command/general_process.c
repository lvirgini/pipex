/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 12:16:28 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	print_error(t_cmd *cmd, int error)
{
	static char	*str_error[NB_ERROR] = {": command not found\n",
		": permission denied\n"};
	static int	error_exit[NB_ERROR] = {127, 126 };

	write(2, "pipex: ", 8);
	if (cmd->argv && cmd->argv[0])
		write(2, cmd->argv[0], ft_strlen(cmd->argv[0]));
	write(2, str_error[error], ft_strlen(str_error[error]));
	close(cmd->pipe[OUT]);
	errno = error_exit[error];
}

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
		print_error(cmd, ERR_CMD_NOT_FOUND);
		return (FAILURE);
	}
	if (access(cmd->path, X_OK) != 0)
	{
		print_error(cmd, ERR_CMD_NOT_EXECUTABLE);
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
	}
	return (pid);
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
	return (WEXITSTATUS(last_status));
}

/*
** 	for pipex : while command next exist, create a pipe between them
** 	create the child processus and keep the pid.
**	close pipe[OUT] not used in PARENT.
** 	close cmd->prev->pipe[IN] not used in PARENT : for ending endless cmd
*/

int	exec_all_commands(t_cmd *cmd, char *env[])
{
	t_cmd	*first;

	first = cmd;
	while (cmd)
	{
		if (cmd->next && pipe(cmd->pipe) == -1)
		{
			perror ("pipe");
			return (FAILURE);
		}
		cmd->pid = create_child_process(cmd, env);
		if (cmd->pid == -1 && cmd->prev)
			close_pipe(cmd->pipe);
		if (cmd->prev)
			close(cmd->prev->pipe[IN]);
		if (cmd->next)
			close(cmd->pipe[OUT]);
		cmd = cmd->next;
	}
	return (wait_all_process(first));
}
