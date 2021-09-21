/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:10:40 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/21 16:29:43 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** PIPEX
**
** usage : 
**	./pipex infile cmd1 cmd2 outfile
**	argv[0] = ./pipex
**	argv[1] = infile
**	argv[2] = cmd1
**	argv[3] = cmd2
**	argv[4] = outfile
*/

static int	print_usage(void)
{
	char	*usage = "pipex usage :\n\nThe execution of the pipex program \
should do the same as the next shell command:\n< infile cmd1 | cmd2 > \
outfile.\n./pipex infile cmd1 cmd2 outfile\n\n";

	write(1, usage, ft_strlen(usage));
	return (-1);
}


int	main(int argc, char *argv[], char *env[])
{
	char	**cmd1;
	char	**cmd2;
	int		infile;
	int		outfile;
	
	if (argc != 5)
		return (print_usage());
	errno = 0;
	infile = open(argv[1], O_RDWR);
	outfile = open(argv[4], O_WRONLY);
	cmd1 = get_argv_for_execve(argv[2]);
	cmd2 = get_argv_for_execve(argv[3]);


	// create pipe
	//lecture sur le pipefd[0] et écriture sur le pipefd[1].
	//	pipefd1 = ecriture de la cmd 1
	//	pipefd0 =  lecture de la cmd 2
	int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

	dup2(infile, pipefd[0]);
	dup2(outfile, pipefd[1]);

	// create fork
    pid_t cpid;
	pid_t cpid2;
	
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) //FILS 1
	{    
        exec_command(cmd1, env);
        exit(EXIT_SUCCESS);
    }
	else 
	{   
		cpid2 = fork();
		if (cpid2 == -1)
		{
       		perror("fork");
        	exit(EXIT_FAILURE);
		}
		if (cpid2 == 0) // FILS 2
		{
       		exec_command(cmd2, env);
        	exit (EXIT_SUCCESS);
		}
	}
	//exec_command(cmd1, env);
	//exec_command(cmd2, env);

	return (0);
}