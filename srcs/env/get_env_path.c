/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:34:17 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 12:13:18 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
** getenv : like getenv
**	return line corresponding to the key from env without key.
*/

char	*get_env(char *env[], char	*key)
{
	size_t	i;
	size_t	len;

	if (!env || !key)
		return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0)
			return (env[i] + len);
		i++;
	}
	return (NULL);
}

/*
** split of line env PATH with ':' as delimitor
*/

char	**split_env(char *env)
{
	char	**split;

	if (!env)
		return (NULL);
	split = ft_split(env, ':');
	if (!split)
		perror("split env");
	return (split);
}

/*
** path of command is needed for execve
** 	check access in absolute path else
** 	'/' is needed between path and command.
** 		ex: PATH=/bin  cmd=ls : test if /bin/ls
** 	search executable with access checking all path
*/

char	*get_path_for_command(t_cmd *cmd, char *path_env[])
{
	size_t	i;
	char	*slash_cmd;

	if (access(cmd->argv[0], F_OK) == 0)
		return (ft_strdup(cmd->argv[0]));
	slash_cmd = ft_strjoin("/", cmd->argv[0]);
	if (!slash_cmd)
	{
		perror("malloc ft_strjoin in get_env");
		return (NULL);
	}
	i = 0;
	while (path_env[i])
	{
		cmd->path = ft_strjoin(path_env[i], slash_cmd);
		if (access(cmd->path, F_OK) == 0)
		{
			free(slash_cmd);
			return (cmd->path);
		}
		free(cmd->path);
		i++;
	}
	free(slash_cmd);
	return (NULL);
}

/*
** get the a plit of 'PATH=' env
** add path to all cmd
*/

int	add_path_for_all_cmd(t_cmd *cmd, char *env[])
{
	char	**path_env;

	path_env = split_env(get_env(env, "PATH="));
	if (!path_env)
		return (FAILURE);
	while (cmd)
	{
		if (cmd->argv && cmd->argv[0])
			cmd->path = get_path_for_command(cmd, path_env);
		cmd = cmd->next;
	}
	free_double_table(path_env);
	return (SUCCESS);
}
