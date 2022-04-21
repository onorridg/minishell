/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/21 17:04:36 by onorridg         ###   ########.fr       */
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

	first_command = string_parser(string, envp);
	command = first_command;
	while (command)
	{
		command->command_parts = command_parts_parser(command);
		command_distribution(command);
		clear_data = command;
		command = command->next;
		clear_command_data(clear_data);
	}
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