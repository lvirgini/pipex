/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_argv_for_execve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:34:25 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/29 12:43:10 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** malloc t_cmd * argc - 3 : ./pipex infile outfile : are not cmd
*/

t_cmd	*get_commands_and_arguments(int argc, char *argv[])
{
	t_cmd	*cmd;
	t_cmd	*first;
	int		i;

	first = create_t_cmd(argv[2], NULL);
	if (!first)
		return (NULL);
	first->input = argv[1];
	cmd = first;
	i = 3;
	while (i < argc - 1)
	{
		cmd->next = create_t_cmd(argv[i], cmd);
		if (!cmd->next)
			free_and_return(first);
		cmd = cmd->next;
		i++;
	}
	cmd->output = argv[argc - 1];
	return (first);
}
