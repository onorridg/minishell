/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/18 17:16:08 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int minishell(char *string, char **envp)
{	
	//BUILTIN **builtins_arr;
	t_command	*command;

	command = string_parser(string, envp);
	while(command)
	{
		printf("%s\n", command->command);
		command = command->next;
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	char	*str;
	
	str = NULL;
	set_terminal_configuration();
	while (TRUE)
	{
		str = readline(BEGIN(49, 31)"root@mac:# "CLOSE);
		add_history(str);
		if (str)
		{
			minishell(str, envp);
			free(str);
		}
		else
		{
			ctrl_d_exit();
			break;
		}
	}
	return (0);
}