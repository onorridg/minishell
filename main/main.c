/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/15 21:35:45 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_command_data(t_command *command)
{	
	if (command && command->command_parts)
		split_free(command->command_parts, -1);
	if (command && command->command)
		free(command->command);
	if (command)
		free(command);
}

static int	exit_minishell(int command_number, char *string)
{	
	display_pipe_data(command_number);
	g_data->error_command = FALSE;
	g_data->error_redirection = FALSE;
	free_pipe_array();
	free(string);
	return (0);
}

static int	minishell(char *string, char **envp)
{
	t_command	*command;
	t_command	*clear_data;
	int			command_number;

	if (pipe_err_parser(string))
		return (1);
	command = string_parser(string, envp);
	if (!command)
		return (1);
	pipe_array();
	command_number = 0;
	while (command && g_data->error_command != FAIL)
	{
		if (config_and_pars(command, string, command_number))
			break ;
		if (g_data->error_redirection == FALSE)
			command_distribution(command);
		command_number += 1;
		clear_data = command;
		command = command->next;
		clear_command_data(clear_data);
	}
	return (exit_minishell(command_number, string));
}

int	main(int ac, char **av, char **envp)
{
	char	*str;

	str = NULL;
	set_terminal_configuration(envp);
	while (TRUE)
	{
		str = readline(BEGIN(49, 33)"root@mac:# "CLOSE);
		add_history(str);
		if (str)
			minishell(str, envp);
		else
			ctrl_d_exit(str);
	}
}
