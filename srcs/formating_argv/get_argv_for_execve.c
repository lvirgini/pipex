/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_for_execve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:34:25 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/22 10:29:04 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** malloc argc - 3 : ./pipex infile outfile : are not cmd
*/

t_cmd	*get_commands_and_arguments(int argc, char *argv[])
{
	t_cmd	*cmd;
	int		i;

	cmd = malloc_t_cmd(argc - 3);
	if (!cmd)
		return (NULL);
	i = 0;
	while (i < argc - 3)
	{
		cmd[i].argv = ft_split(argv[i + 2], ' ');
		if (!cmd[i].argv)
		{
			perror("Malloc ft_split");
			free_t_cmd(cmd, i - 1);
			return (NULL);
		}
		i++;
	}
	return (cmd);
}
