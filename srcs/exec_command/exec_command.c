/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:53:58 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/30 20:44:47 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execve_this_command(t_cmd *cmd, char *env[])
{
	int		ret;

	ret = execve(cmd->path, cmd->argv, env);
	if (ret == -1)
	{
		perror("execve error");
		return (-1);
	}
	return (0);
}
