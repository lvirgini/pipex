/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:09:08 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/29 12:39:17 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double_table(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

/*
** Free all t_cmd
*/

void	free_t_cmd(t_cmd *cmd)
{
	t_cmd	*to_free;

	while (cmd)
	{
		if (cmd->argv)
			free_double_table(cmd->argv);
		if (cmd->path)
			free(cmd->path);
		to_free = cmd->next;
		free(cmd);
		cmd = to_free;
	}
}

/*
** Malloc t_cmd, get cmd->prev and create split of arguments.
*/

t_cmd	*malloc_t_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("malloc t_cmd");
		return (NULL);
	}
	ft_memset(cmd, 0, sizeof(t_cmd));
	cmd->path = NULL;
	cmd->argv = NULL;
	cmd->input = NULL;
	cmd->output = NULL;
	return (cmd);
}

t_cmd	*create_t_cmd(char *argv, t_cmd *prev)
{
	t_cmd	*cmd;

	cmd = malloc_t_cmd();
	if (cmd)
	{
		cmd->prev = prev;
		if (argv && argv[0])
		{
			cmd->argv = ft_split(argv, ' ');
			if (!cmd->argv)
			{
				perror("malloc ft_split");
				return (NULL);
			}
		}
	}
	return (cmd);
}
