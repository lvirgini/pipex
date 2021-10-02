/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 14:53:58 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 09:26:00 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execve_this_command(t_cmd *cmd, char *env[])
{
	int	ret;

	ret = execve(cmd->path, cmd->argv, env);
	perror("execve");
	if (cmd->prev)
		close(cmd->prev->pipe[IN]);
	close(cmd->pipe[OUT]);
	free_and_return(cmd);
	exit(ret);
}
