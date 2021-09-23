/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:59:50 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/23 20:36:04 by lvirgini         ###   ########.fr       */
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

int	set_up_files_descriptor(int	*infile, int *outfile, char *argv[])
{
	*infile = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (*infile == -1)
		perror(argv[1]);
	else if (dup2(*infile, 0) == -1)
	{
		close(*infile);
		perror("dup2");
		return (FAILURE);
	}
	*outfile = open(argv[4], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP);
	if (*outfile == -1 || dup2(*outfile, 1) == -1)
	{
		close(*infile);
		close(*outfile);
		perror("dup2");
		return (FAILURE);
	}
	return (SUCCESS);
}
