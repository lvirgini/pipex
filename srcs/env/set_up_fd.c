/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:59:50 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/28 17:51:35 by lvirgini         ###   ########.fr       */
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

int	set_up_input(int std_io[2], char *input)
{
	std_io[IN] = open(input, O_RDONLY | O_CLOEXEC);
	if (std_io[IN] == -1)
	{
		perror(input);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	set_up_output(int std_io[2], char *output)
{
	std_io[OUT] = open(output, O_CREAT | O_TRUNC | O_WRONLY,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (std_io[OUT] == -1)
		perror(output);
	else if (dup2(std_io[OUT], 1) == -1)
		perror("dup2 set up output");
	else
		return (SUCCESS);
	return (FAILURE);
}

/*
** if first cmd : get infile to input
** else get cmd last input to input
**
** if last cmd => not pipe
** else make cmd pipe output to output
*/

void	set_up_io_in_fork(t_cmd *cmd, int std_io[2])
{
	dprintf(2, "%s : input = %d\n",cmd->path, cmd->prev->pipe[IN]);
	if (cmd->prev)
	{
		if (dup2(cmd->prev->pipe[IN], 0) == -1)
		{
			perror ("dup2");
			exit(EXIT_FAILURE);
		}
	}
	else if (dup2(std_io[IN], 0) == -1)
	{
		perror ("dup2");
		exit(EXIT_FAILURE);
	}
	if (cmd->next)
	{
		if (dup2(cmd->pipe[OUT], 1) == -1)
		{
			perror ("dup2");
			exit(EXIT_FAILURE);
		}
		close(cmd->pipe[IN]);
	//	dprintf(2, "%s : output = %d pipe input = %d\n",cmd->path, cmd->pipe[OUT], cmd->pipe[IN]);
	}	

}