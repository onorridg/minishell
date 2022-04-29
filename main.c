/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/29 15:53:13 by onorridg         ###   ########.fr       */
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
		command->command_number = command_number;
		command->command_parts = command_parts_parser(command);
		command_distribution(command);
		command_number += 1;
		clear_data = command;
		command = command->next;
		clear_command_data(clear_data);
	}
	close(g_data->pipe_array[command_number - 1][1]);
	//fprintf(stderr, "PRINT RESULT\n");
	while (read(g_data->pipe_array[command_number - 1][0], output, 1) > 0)
	{
		write(1, output, 1);
	}
	close(g_data->pipe_array[command_number - 1][0]);
	//printf("OUT2\n");
	//fflush(stdout);	
	g_data->command_counter = 0;
	//free(string);
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*str;
	
	str = NULL;
	set_terminal_configuration(envp);
	rl_outstream = stderr; // ??
	while (TRUE)
	{
		str = readline(CLOSE BEGIN(49, 33)"➜ root@mac:# "CLOSE);
		add_history(str);
		if (str)
			minishell(str, envp);
		else
			ctrl_d_exit();
	}
}