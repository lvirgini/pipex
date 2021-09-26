/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:10:40 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/26 23:29:03 by lvirgini         ###   ########.fr       */
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
	static char	*usage = "pipex usage :\n\nThe execution of the pipex program \
should do the same as the next shell command:\n< infile cmd1 | cmd2 > \
outfile.\n./pipex infile cmd1 cmd2 outfile\n\n";

	write(1, usage, ft_strlen(usage));
	return (-1);
}

/*
** CREATION T_CMD : recuperation des arguments pour chaque cmd
**	recuperation des path pour chaque commande
** mise en place des fd du programme principal :
**
*/

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	int		infile;//
	int		outfile;//

	if (argc != 5)
		return (print_usage());
	errno = 0;
	cmd = get_commands_and_arguments(argc, argv);
	if (!cmd)
		return (errno);
	if (add_path_for_all_cmd(cmd, env) == FAILURE)
		return (free_and_return(cmd));
	if (set_up_files_descriptor(&infile, &outfile, argv) == FAILURE)
		return (free_and_return(cmd));
	make_pipex(cmd, env);
	free_and_return(cmd);
	return (0);
}
