/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:35:32 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/27 13:32:44 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void rewrite_command_part_arr(t_command *command, int part)
{
	int i;

	i = part + 2;
	free(command->command_parts[part]);
	free(command->command_parts[part + 1]);
	command->command_parts[i] = NULL;
	command->command_parts[i] = NULL;
	while (command->command_parts[i])
		command->command_parts[part++] = command->command_parts[i++];
		
	
}

static void	set_new_pipe(t_command *command)
{
	close(g_data->pipe_array[command->command_number][0]);
	close(g_data->pipe_array[command->command_number][1]);
	if (pipe(g_data->pipe_array[command->command_number]) == -1)
		exit(1);
}

static void redirect_input(t_command *command, int part)
{	
	int		fd;
	char 	buf[1];
	int 	read_ch;
	int		*pipe_fds;
	
	read_ch = 1;
	if (command->command_parts[part + 1])
	{	
		fd = open(command->command_parts[part + 1], O_RDONLY);
		if (fd == -1)
			error_handler(command);
		
		set_new_pipe(command);
		pipe_fds = g_data->pipe_array[command->command_number];
		while (read_ch)
		{
			read_ch = read(fd, buf, 1);
			write(pipe_fds[1], buf, 1);
		}
	}
	else 
	{
		printf("syntax error near unexpected token `newline'\n");
		fflush(stdout);
	}
}

void	redirections(t_command *command)
{	
	int part;
	
	part = 0;
	while(command->command_parts[part])
	{
		if (ft_strcmp(command->command_parts[part], "<"))
			redirect_input(command, part);
		part++;
	}
}