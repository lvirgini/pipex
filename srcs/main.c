/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:10:40 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 10:56:00 by lvirgini         ###   ########.fr       */
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

	write(2, usage, ft_strlen(usage));
	errno = 22;
	return (errno);
}

/*
** PIPEX
**
**	argument must be 5 ./pipex infile cmd1 cmd2 outfile
**	create list of commands with theirs own arguments
**	get path for all command with env
** 	execute all command
** 	PARENT can free all allocated memory
**	return the last child processus exit status
*/

int	main(int argc, char *argv[], char *env[])
{
	t_cmd	*cmd;
	int		ret;

	if (argc != 5)
		return (print_usage());
	errno = 0;
	cmd = get_commands_and_arguments(argc, argv);
	if (!cmd)
		return (errno);
	add_path_for_all_cmd(cmd, env);
	ret = exec_all_commands(cmd, env);
	free_and_return(cmd);
	return (ret);
}
