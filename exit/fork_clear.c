/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:48:10 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 15:03:47 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void clear_fork_mem(t_command *command, char *path)
{	
	int i;
	t_command *clear;

	i = 0;
	while(command)
	{	
		clear = command;
		command = command->next;
		split_free(clear->command_parts, -1);
		free(clear->command);
		free(clear);
	}
	free_pipe_array();
	free_all_envp();
	free(g_data);
	free(path);
	while (g_data->builtin_functions[i])
	{
		free(g_data->builtin_functions[i++]);
	}
	free(g_data->builtin_functions);
}