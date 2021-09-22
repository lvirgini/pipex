/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 00:09:08 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/22 18:52:38 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_double_table(char **s) // name ? 
{
	size_t	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

void	free_t_cmd(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].argv)
			free_double_table(cmd[i].argv);
		if (cmd[i].path)
			free(cmd[i].path);
		i++;
	}
	free(cmd);
}

t_cmd	*malloc_t_cmd(int nb_cmd)
{
	t_cmd	*cmd;
	
	cmd = (t_cmd *)malloc(sizeof(t_cmd) * nb_cmd);
	if (!cmd)
		perror("malloc t_cmd");
	ft_memset(cmd, 0, sizeof(cmd) * nb_cmd);
	return (cmd);
}
