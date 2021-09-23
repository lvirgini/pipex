/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:53:58 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/23 16:00:24 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_command(t_cmd *cmd, char *env[])
{
	printf ("[%s]\n", cmd->path);//
	for(int i = 0; cmd->argv[i]; i++)//
		printf("\targv[%d] = %s\n", i, cmd->argv[i]);//
	int ret = execve(cmd->path ,cmd->argv, env);
    if (ret == -1)
    {
		perror("execve error");
		return (-1);
	}
	return (0);
}