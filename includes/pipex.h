/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 10:07:15 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/21 16:36:11 by lvirgini         ###   ########.fr       */
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


/*
** ARGUMENTS
*/

char	**get_argv_for_execve(char	*arguments);
int		exec_command(char	**cmd, char	*env[]);

/*
** UTILS FUNCTIONS
*/

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_strchr_len(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup_max(const char *s, size_t max);
char	**ft_split(const char *s, const char c);

#endif
