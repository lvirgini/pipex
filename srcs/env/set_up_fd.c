/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:59:50 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/22 19:10:48 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** change standard input by infile 
** change standard output by outfile
*/

int	set_up_files_descriptor(int	*infile, int *outfile, char *argv[])
{
	// ouverture infile en lecture seule avec close(fd) car utilisé avec execve
	*infile = open(argv[1], O_RDONLY | O_CLOEXEC);
	if (*infile == -1)
	{
		perror(argv[1]);
		return (FAILURE);
	}
	// ouvreture outfile avec creation possible et tous les droits (j'ai pas tout bien compris)
	//dans le shell creation comme ca : -rw-r--r-- 1 mini mini     0 sept. 21 17:47 outfile
	*outfile = open(argv[4], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP);
	if (*outfile == -1)
	{
		close (*infile);
		perror(argv[1]);
		return (FAILURE);
	}
	if (dup2(*infile, 0) == -1 || dup2(*outfile, 1) == -1)
	{
		close(*infile);
		close(*outfile);
		perror("dup2");
		return (FAILURE);
	}
	return (SUCCESS);
}
