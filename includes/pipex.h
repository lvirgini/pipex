/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:07:15 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 12:17:08 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include "pipex_utils.h"
# include "pipex_structure.h"
# include "pipex_error.h"

enum	e_stdio
{
	IN,
	OUT,
};

enum	e_bool
{
	SUCCESS,
	FAILURE,
};

/*
** ARGUMENTS
*/

t_cmd	*get_commands_and_arguments(int argc, char *argv[]);
int		make_pipex(t_cmd *cmd, char *env[]);
int		exec_all_commands(t_cmd *cmd, char *env[]);
int		execve_this_command(t_cmd *cmd, char *env[]);

/*
** ENVIRONNEMENT | PATHS
*/

int		add_path_for_all_cmd(t_cmd *cmd, char *env[]);
int		set_up_io_in_fork(t_cmd *cmd);
void	close_pipe(int pipe[2]);

#endif
