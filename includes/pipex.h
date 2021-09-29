/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:07:15 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/29 17:28:14 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include "pipex_utils.h"

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

enum	e_type
{
	PIPE,
	AND,
};

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char	**argv;
	char	*path;
	char	*input;
	char	*output;
	int		pipe[2];
	int		type;
	pid_t	pid;
	t_cmd	*next;
	t_cmd	*prev;
};

/*
** STRUCTURES
*/

void	free_t_cmd(t_cmd *cmd);
t_cmd	*malloc_t_cmd(void);
t_cmd	*create_t_cmd(char *argv, t_cmd *prev);

/*
** ARGUMENTS
*/

int		make_pipex(t_cmd *cmd, char *env[]);
t_cmd	*get_commands_and_arguments(int argc, char *argv[]);
int		exec_command(t_cmd *cmd, char *env[]);

/*
** ENVIRONNEMENT | PATHS
*/

int		add_path_for_all_cmd(t_cmd *cmd, char *env[]);
void	set_up_io_in_fork(t_cmd *cmd);

/*
** ERRORS
*/

int		free_and_return(t_cmd *cmd);

#endif
