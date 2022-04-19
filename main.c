/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/19 19:13:24 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int minishell(char *string, char **envp)
{	
	t_command			*first_command;
	t_command			*command;
	//t_shell_variable	*var;

	first_command = string_parser(string, envp);
	command = first_command;
	while (command)
	{
		command->command_parts = command_parts_parser(command);
		command_distribution(command);
		command = command->next;
	}
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
		{
			minishell(str, envp);
			free(str);
		}
		else
		{
			ctrl_d_exit();
			exit(0);
			//break;
		}
	}
	return (0);
}