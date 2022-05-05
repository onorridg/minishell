/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:55:00 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/04 15:01:47 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void error_redirection_handler(t_command *command, char *file_n)
{
	g_data->error_status = FAIL;
	g_data->exit_code = 1;
	set_exit_code(g_data->exit_code);
	write(1, "minishell: ", 11);
	write(1, file_n, ft_strlen(file_n));
	write(1, ": ", 2);
	write(1, strerror(errno), strlen(strerror(errno)));
	write(1, "\n", 1);
}

static char **alloc_mem_for_arr(char **array)
{
	int 	len;
	char	**new_arr;
	
	len = 0;
	while (array[len])
		len++;
	new_arr = (char **)malloc(sizeof(char *) * (len * 10));
	if (!new_arr)
		exit(1);
	return (new_arr);
}

void rewrite_command_part_arr(t_command *command, int part)
{
	int i;
	int k;
	char **new_arr;
	
	i = 0;
	new_arr = alloc_mem_for_arr(command->command_parts);
	while (command->command_parts[i] && i < part )
	{
		new_arr[i] = command->command_parts[i];
		i++;
	}
	free(command->command_parts[i]);
	free(command->command_parts[i + 1]);
	k = i + 2;
	while(command->command_parts[k])
		new_arr[i++] = command->command_parts[k++];
	free(command->command_parts);
	new_arr[i] = NULL;
	command->command_parts = new_arr;
}

void get_pipe(t_command *command)
{	
	int pipe_fds[2];
	
	if (pipe(pipe_fds) == -1)
	{	
		printf("new pipe fail\n");
		fflush(stdout);
		exit(1);
	}
	if (command->file_pipe[0] != -1)
		close(command->file_pipe[0]);
	command->file_pipe[0] = pipe_fds[0];
	command->file_pipe[1] = pipe_fds[1];
}