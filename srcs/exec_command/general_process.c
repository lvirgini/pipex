/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 22:17:28 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/23 18:08:20 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	creating_process(t_cmd *cmd, int input_fd[2], int output_fd[2], char *env[])
{
	pid_t cpid;

	cpid = fork();
    if (cpid == -1) {
        perror("fork");
        return(-1);
    }
	if (cpid == 0)
	{
		if (input_fd[1] != -1)
			close (input_fd[1]);
		if (output_fd[0] != -1)
			close(output_fd[0]);
		if (dup2(input_fd[0], 0) == -1 || dup2(output_fd[1], 1) == -1)
			perror("dup2");
		exec_command(cmd, env);
		exit(EXIT_SUCCESS);
	}
	else 
	{
		if (input_fd[0] != -1)
			close (input_fd[0]);
		if (output_fd[1] != -1)
			close(output_fd[1]);
	}
	return (cpid);
}

int	make_pipex(t_cmd *cmd, int nb_cmd, int outfile, char *env[])
{
	int		i;
	int		input_fd[2];
	int		output_fd[2];
	
	i = 0;
	input_fd[0] = dup(0);
	if (input_fd[0] == -1)
		perror("dup");
	input_fd[1] = -1;
	while (i < nb_cmd - 1)
	{
		if (pipe(output_fd) == -1)
		{
			perror("pipe");
			return (FAILURE);
		}
		if (creating_process(&cmd[i], input_fd, output_fd, env) == -1)
			return (FAILURE);
		i++;
		input_fd[0] = output_fd[0];
		input_fd[1] = output_fd[1];
	}
	output_fd[1] = outfile;
	output_fd[0] = -1;
	if (creating_process(&cmd[i], input_fd, output_fd, env) == -1)
		return (FAILURE);
	return (SUCCESS);
}