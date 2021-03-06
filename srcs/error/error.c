/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:13 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 12:14:46 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** Free all allocated memory in PARENT. 
** if execve error : CHILD can free all too.
*/

int	free_and_return(t_cmd *cmd)
{
	while (cmd->prev)
		cmd = cmd->prev;
	free_t_cmd(cmd);
	return (errno);
}

void	close_pipe(int pipe[2])
{
	close(pipe[IN]);
	close(pipe[OUT]);
}
