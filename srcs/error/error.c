/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvirgini <lvirgini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 11:09:13 by lvirgini          #+#    #+#             */
/*   Updated: 2021/09/26 22:33:37 by lvirgini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_and_return(t_cmd *cmd)
{
	free_t_cmd(cmd);
	return (errno);
}
