/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_pipe_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:42:57 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 18:21:54 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_command	*alloc_mem_com(void)
{
	return ((t_command *)malloc(sizeof(t_command)));
}

int	exec_open_pipe_command(t_command *command)
{
	char	*str;

	str = readline("> ");
	if (!str)
		return (1);
	if (!command)
		exit(1);
	command->command = str;
	return (0);
}
