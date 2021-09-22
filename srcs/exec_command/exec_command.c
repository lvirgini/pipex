/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:53:58 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/22 19:17:58 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_command(t_cmd *cmd, char *env[])
{
	//char path[256] = "/bin/"; // ou malloc ?
	//ft_strlcat(path, cmd[0], 256);
	printf ("[%s]\n", cmd->path);
	int ret = execve(cmd->path ,cmd->argv, env);
    if (ret == -1)
    {
		perror("execve error");
		return (-1);
	}
	return (0);
}