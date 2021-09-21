/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:09:08 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/22 00:22:32 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_double_table(char **s) // name ? 
{
	size_t	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	free_t_cmd(t_cmd *cmd, int nb_cmd)
{
	while (nb_cmd)
	{
		free_double_table((cmd + nb_cmd)->argv);
		nb_cmd--;
	}
	free (cmd);
}

t_cmd	*malloc_t_cmd(int nb_cmd)
{
	t_cmd	*cmd;
	
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * nb_cmd);
	if (!cmd)
		perror("malloc t_cmd");
	return (cmd);
}
