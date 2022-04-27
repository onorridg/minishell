/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_pipe_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:42:57 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/27 12:07:09 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_command	*alloc_mem_com(void)
{
	return ((t_command *)malloc(sizeof(t_command)));
}

void	exec_open_pipe_command(t_command *command)
{
	char		*str;
	
	str = readline("> ");
	if (!command)
		exit(1);
	free(command->command);
	split_free(command->command_parts, -1);
	command->command = str;
	command->command_parts = command_parts_parser(command);
	command_distribution(command);	
}