/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:10:40 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/22 18:36:53 by lvirgini         ###   ########.fr       */
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
	t_cmd	*cmd;
	int		infile;
	int		outfile;
	
	if (argc != 5)
		return (print_usage());
	errno = 0;

/// CREATION T_CMD : recuperation des arguments pour chaque cmd
	cmd = get_commands_and_arguments(argc, argv);
	if (!cmd)
		return (-1); //
	if (add_path_for_all_cmd(cmd, env, argc - 3) == SUCCESS)
		return (free_and_return(cmd, 2));



	
	return (free_and_return(cmd, 2));

///		il faut recuperer le bon  PATH des cmds avec env /! :	

/// MISE EN PLACE DES FD
/// PIPE
/// FORK
/// execution des process
/// attente de la fin de tous les process.



	//if (opening_file(&infile, &outfile, argv) == FAILURE)
	//	return (free_and_return(cmd1, cmd2));


	// ouverture infile en lecture seule avec close(fd) car utilisé avec execve
	infile = open(argv[1], O_RDONLY | O_CLOEXEC);
		// ouvreture outfile avec creation possible et tous les droits (j'ai pas tout bien compris)
	//dans le shell creation comme ca : -rw-r--r-- 1 mini mini     0 sept. 21 17:47 outfile
	outfile = open(argv[4], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP);


	// redirection des FD pour correspondre a pipex
	//	fd0 devient infile
	//	fd01 devient outfile
	dup2(infile, 0);
	dup2(outfile, 1);
	//write(1, "test\n", 5); OK

	// create pipe
	//lecture sur le pipefd[0]  et écriture sur le pipefd[1].
	//  cmd 1 -> pipefd1 = sortie std (1) -----> pipefd0 = entrée std (0) -> cmd 2
	int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

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
		// dans le fils : redirection fd : la sortie std du fils deviens l'entrée std du second fils
		if (dup2(pipefd[1], 1) == -1)
     		perror("dup2");
		//write (1, "test\n", 5);
        exec_command(cmd[0].argv, env);
        exit(EXIT_SUCCESS);
    }
	else 
	{
		wait(NULL);
		cpid2 = fork();
		if (cpid2 == -1)
		{
       		perror("fork");
        	exit(EXIT_FAILURE);
		}
		if (cpid2 == 0) // FILS 2
		{
			//char	buffer[1024];
   			//int		ret;
   			//int		status;

			close(pipefd[1]);
			if (dup2(pipefd[0], 0) == -1)
     			perror("dup2");
       		exec_command(cmd[1].argv, env);
        	exit (EXIT_SUCCESS);
		}
	}

	return (0);
}