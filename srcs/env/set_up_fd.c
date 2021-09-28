/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:59:50 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/28 12:47:09 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** change standard input by infile  (readonly and close if execve)
** change standard output by outfile (create if not exist)
** dans le shell creation comme ca : -rw-r--r-- 1  outfile
**
** if open can't find infile, display error and continue;
** if open can't create outfile : rdisplay error and exit.
*/
/*
int		set_up_input(char *file, int *fd)
{
	*fd == open(file, O_RDONLY | O_CLOEXEC);
	if (*fd == -1)
		perror(file);
	else if (dup2(*fd, 0) == -1)
	{	
		close(*fd);
		perror("dup2 set up files descriptor");
	}
	else
		return (SUCCESS);
	return (FAILURE);
	
}
*/
int	set_up_input(int std_io[2], char *input)
{
	std_io[IN] = open(input, O_RDONLY | O_CLOEXEC);
	if (std_io[IN] == -1)
		perror(input);	
	else if (dup2(std_io[IN], 0) == -1)
		perror("dup2 set up files descriptor");
	else
		return (SUCCESS);
	return (FAILURE);
	
}

int	set_up_output(int std_io[2], char *output)
{
	std_io[OUT] = open(output, O_CREAT | O_TRUNC | O_WRONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (std_io[OUT] == -1)
		perror(output);
	else if (dup2(std_io[OUT], 1) == -1)
		perror("dup2 set up files descriptor");
	else
		return (SUCCESS);
	return (FAILURE);
}

/*
int		set_up_files_descriptor(int	std_io[2], char *input, char *output)
{
	std_io[IN] = open(input, O_RDONLY | O_CLOEXEC);
	if (std_io[IN] == -1)
		perror(input);	
	else if (dup2(std_io[0], 0) == -1)
		perror("dup2 set up files descriptor");

	std_io[OUT] = open(output, O_CREAT | O_TRUNC | O_WRONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (std_io[OUT] == -1 || dup2(std_io[OUT], 1) == -1)
	{
		perror("dup2 set up files descriptor");
		return (FAILURE);
	}
	return (SUCCESS);
}
*/