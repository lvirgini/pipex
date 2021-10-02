/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:59:50 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 10:48:35 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
**	INFILE		PIPE 1			PIPE 2			PIPE 3			OUTFILE
**	 --0	1-----------0	1-----------0	1-----------0	1-----
**	|	CD1		|		CD2		|		CD3		|		CD4		|
**
*/

/*
** 	IN FORK : 
**	change standard input by infile
**		O_RDONLY : only reading file
**		O_CLOEXEC : close automatically at the end of execve
** 	if open can't find infile, display error.
*/

static int	set_up_input(t_cmd *cmd, char *input)
{
	int	fd;

	fd = open(input, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
		perror(input);
	else if (dup2(fd, IN) == -1)
		perror("dup2 set up input");
	else
	{
		close(cmd->pipe[IN]);
		return (SUCCESS);
	}
	return (FAILURE);
}

/*
** 	change standard output by outfile (create if not exist)
**		O_CREAT with all option needed : -rw-r--r--
** 		O_TRUNC : if exist 
**	display error and exit.
*/

static int	set_up_output(char *output)
{
	int		fd;

	fd = open(output, O_CREAT | O_TRUNC | O_WRONLY | O_SYNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		perror(output);
	else if (dup2(fd, OUT) == -1)
		perror("dup2 set up output");
	else
		return (SUCCESS);
	return (FAILURE);
}

/*
**	change standard input by pipe[IN] of cmd prev
*/

static int	set_up_pipe_input(t_cmd *cmd)
{
	if (cmd->prev)
	{
		if (dup2(cmd->prev->pipe[IN], IN) == -1)
		{
			perror ("dup2 set_up_io_in_fork: input");
			close (cmd->pipe[OUT]);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

/*
**	change standard output by pipe[OUT] of this cmd
*/

static int	set_up_pipe_output(t_cmd *cmd)
{
	if (dup2(cmd->pipe[OUT], OUT) == -1)
	{
		perror ("dup2 set_up_io_in_fork: output");
		return (FAILURE);
	}
	close(cmd->pipe[IN]);
	return (SUCCESS);
}

/*
** if cmd have input file :  get infile to input
** else get cmd last pipe[IN] to input
**
** if cmd have output file : get outfile to output
** else get cmd pipe[OUT] to output
*/

int	set_up_io_in_fork(t_cmd *cmd)
{
	if (cmd->input)
	{
		if (set_up_input(cmd, cmd->input) == FAILURE)
			return (FAILURE);
	}
	else
	{
		if (set_up_pipe_input(cmd) == FAILURE)
			return (FAILURE);
	}
	if (cmd->output)
	{
		if (set_up_output(cmd->output) == FAILURE)
			return (FAILURE);
	}	
	else
	{
		if (set_up_pipe_output(cmd) == FAILURE)
			return (FAILURE);
	}
	return (SUCCESS);
}
