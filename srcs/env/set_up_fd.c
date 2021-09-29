/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:59:50 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/29 16:55:06 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** change standard input by infile  (readonly and close if execve)
** change standard output by outfile (create if not exist)
**
** if open can't find infile, display error and continue;
** if open can't create outfile : rdisplay error and exit.
*/

static void	set_up_input(t_cmd *cmd, char *input)
{
	int	fd;

	fd = open(input, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
		perror(input);
	else if (dup2(fd, 0) == -1)
		perror("dup2 set up input");
	else
		return ;			
	close(cmd->pipe[OUT]);
	exit(EXIT_FAILURE);

}

static void	set_up_output(t_cmd *cmd, char *output)
{
	int		fd;
	
	fd = open(output, O_CREAT | O_TRUNC | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror(output);
	else if (dup2(fd, 1) == -1)
		perror("dup2 set up output");
	else
		return ;
	close(cmd->pipe[OUT]);
	exit(EXIT_FAILURE);
}

/*
** if first cmd : get infile to input
** else get cmd last input to input
**
** if last cmd => not pipe
** else make cmd pipe output to output
*/

void	set_up_io_in_fork(t_cmd *cmd)
{
	//dprintf(2, "%s : input = %d\n",cmd->path, cmd->prev->pipe[IN]);
	if (cmd->input)
		set_up_input(cmd, cmd->input);
	else if (cmd->prev && cmd->prev->type == PIPE)
	{
		if (dup2(cmd->prev->pipe[IN], 0) == -1)
		{
			perror ("dup2 set_up_io_in_fork: input");
			close (cmd->pipe[OUT]);
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->output)
		set_up_output(cmd, cmd->output);
	else if (cmd->type == PIPE)
	{
		if (dup2(cmd->pipe[OUT], 1) == -1)
		{
			perror ("dup2 set_up_io_in_fork: output");
			exit(EXIT_FAILURE);
		}
		close(cmd->pipe[IN]);
	}
	//	dprintf(2, "%s : output = %d pipe input = %d\n",cmd->path, cmd->pipe[OUT], cmd->pipe[IN]);
}

