/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:53:58 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/22 11:52:08 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exec_command(char **cmd, char *env[])
{
	char path[256] = "/bin/"; // ou malloc ?
	ft_strlcat(path, cmd[0], 256);
	printf ("[%s]\n", path);
	int ret = execve(path ,cmd, env);
    if (ret == -1)
    {
		perror("execve error");
		return (-1);
	}
	return (0);
}