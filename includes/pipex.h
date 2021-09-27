/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:07:15 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/27 18:16:03 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> //
# include <sys/wait.h> //
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

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char	**argv;
	char	*path;
	int		pipe[2];
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

int		make_pipex(t_cmd *cmd, char *env[], char *input, char *output);
t_cmd	*get_commands_and_arguments(int argc, char *argv[]);
int		exec_command(t_cmd *cmd, char *env[]);

/*
** ENVIRONNEMENT | PATHS
*/

int		add_path_for_all_cmd(t_cmd *cmd, char *env[]);
int		set_up_input(int std_io[2], char *input);
int		set_up_output(int std_io[2], char *output);

/*
** ERRORS
*/

int		free_and_return(t_cmd *cmd);

#endif
