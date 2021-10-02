/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_structure.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:27:21 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 11:30:53 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_STRUCTURE_H
# define PIPEX_STRUCTURE_H

typedef struct s_cmd	t_cmd;
struct s_cmd
{
	char	**argv;
	char	*path;
	char	*input;
	char	*output;
	int		pipe[2];
	pid_t	pid;
	t_cmd	*next;
	t_cmd	*prev;
};

void	free_t_cmd(t_cmd *cmd);
t_cmd	*malloc_t_cmd(void);
t_cmd	*create_t_cmd(char *argv, t_cmd *prev);

#endif
