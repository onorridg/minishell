/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/25 16:16:18 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	clear_command_data(t_command *command)
{	
	//split_free(command->command_parts, -1);
	free(command->command);
	free(command);
	//printf("[+] CLEARED \n");
}

static int minishell(char *string, char **envp)
{	
	t_command			*first_command;
	t_command			*command;
	t_command			*clear_data;
	int					command_number;
	pid_t				pid;
	int					*pipe_fds;
	char				output[1];
	
	first_command = string_parser(string, envp);
	command = first_command;
	pipe_array();
	command_number = 0;
	while (command)
	{
		pipe_fds = g_data->pipe_array[command_number];
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			close(pipe_fds[0]);						
			if (command_number == 0) 	
			{													//close(pipefds[0]); rewrite, dose not close if << or <
				if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
					exit(1);
			}
			else
			{
				pipe_fds[0] = g_data->pipe_array[command_number - 1][0];
				if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
					exit(1);
				if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
					exit(1);
			}
			
			command->command_number = command_number;
			command->command_parts = command_parts_parser(command);
			command_distribution(command);
			exit(0);
		}
		//wait4(pid, NULL, WNOHANG, NULL);
		close(pipe_fds[1]);
		command_number += 1;
		clear_data = command;
		command = command->next;
		clear_command_data(clear_data);
	}
	while (read(pipe_fds[0], output, 1))
		write(1, output, 1);
	close(pipe_fds[0]);
	g_data->command_counter = 0;
	free(string);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*str;
	
	str = NULL;
	set_terminal_configuration(envp);
	//rl_outstream = stderr; // ??
	while (TRUE)
	{
		str = readline(BEGIN(49, 33)"➜ root@mac:# "CLOSE);
		add_history(str);
		if (str)
			minishell(str, envp);
		else
			ctrl_d_exit();
	}
}