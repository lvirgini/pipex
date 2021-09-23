/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:07:15 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/23 20:15:57 by lvirgini         ###   ########.fr       */
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

enum	e_bool
{
	SUCCESS,
	FAILURE,
};

typedef struct s_cmd
{
	char	**argv;
	char	*path;
}	t_cmd;

/*
** STRUCTURES
*/

void	free_t_cmd(t_cmd *cmd, int nb_cmd);
t_cmd	*malloc_t_cmd(int nb_cmd);

/*
** ARGUMENTS
*/

int		make_pipex(t_cmd *cmd, int nb_cmd, int outfile, char *env[]);
t_cmd	*get_commands_and_arguments(int argc, char *argv[]);
int		exec_command(t_cmd *cmd, char *env[]);

/*
** ENVIRONNEMENT | PATHS
*/

int		add_path_for_all_cmd(t_cmd *cmd, char *env[], int nb_cmd);
int		set_up_files_descriptor(int	*infile, int *outfile, char *argv[]);

/*
** ERRORS
*/

int		free_and_return(t_cmd *cmd, int nb_cmd);

#endif
