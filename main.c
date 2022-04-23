/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/23 13:13:34 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	clear_command_data(t_command *command)
{	
	split_free(command->command_parts, -1);
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
	
	first_command = string_parser(string, envp);
	command = first_command;
	ft_pipe_array();
	command_number = 0;
	while (command)
	{	
		/*pid = fork();
		if (pid == -1)
			exit(1);*/
		command->command_number = command_number++;
		command->command_parts = command_parts_parser(command);
		command_distribution(command);
		clear_data = command;
		command = command->next;
		clear_command_data(clear_data);
	}
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
		str = readline(BEGIN(49, 35) BLOD "➜ " BEGIN(49, 33)"root@mac:# "CLOSE);
		add_history(str);
		if (str)
			minishell(str, envp);
		else
			ctrl_d_exit();
	}
}