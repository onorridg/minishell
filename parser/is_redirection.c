/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:56:48 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 12:11:00 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../minishell.h"

int	*is_redirection(t_command *command)
{
	int	*pipes;
	
	pipes = (int *)malloc(sizeof(int) * 2);
	if (!pipes)
		exit(1);
	pipes[0] = g_data->pipe_array[command->command_number][0];
	pipes[1] = g_data->pipe_array[command->command_number][1];
	if (command->file_pipe[0] != -1)
		pipes[0] = command->file_pipe[0];
	if (command->file_pipe[1] != -1)
		pipes[1] = command->file_pipe[1];
	return (pipes);
}