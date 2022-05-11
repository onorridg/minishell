/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_pipe_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:42:57 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 13:19:21 by onorridg         ###   ########.fr       */
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
	//printf("command_number[%i] == g_data->command_count[%i]\n", command->command_number, g_data->command_count);
	
	str = readline("> ");
	if (!str)
		return;
	if (!command)
		exit(1);
	command->command = str;	
}