/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 11:25:48 by lvirgini          #+#    #+#             */
/*   Updated: 2021/10/02 11:29:49 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_ERROR_H
# define PIPEX_ERROR_H

# define NB_ERROR 2

enum	e_error
{
	ERR_CMD_NOT_FOUND,
	ERR_CMD_NOT_EXECUTABLE,
};

int		free_and_return(t_cmd *cmd);

#endif