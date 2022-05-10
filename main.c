/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/10 14:59:20 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	clear_command_data(t_command *command)
{	
	if (command && command->command_parts)
		split_free(command->command_parts, -1);
	if (command && command->command)
		free(command->command);
	if (command)
		free(command);
	//printf("[+] CLEARED \n");
}

static int minishell(char *string, char **envp)
{	
	t_command			*first_command;
	t_command			*command;
	t_command			*clear_data;
	int					command_number;
	int					*pipe_fds;
	char 				*output[1];
	
	first_command = string_parser(string, envp);
	if (!first_command)
		return (0);
	command = first_command;
	pipe_array();
	command_number = 0;
	while (command)
	{
		g_data->error_redirection = FALSE;
		g_data->error_command = FALSE;
		command->command_number = command_number;
		/*if (ft_find_char_in_string(string, '|') != -1)
		{
			write(1, "minishell: ", 11);
			write(1, "syntax error near unexpected token `|'\n", 39);
			g_data->error_redirection = FAIL;
			free(command);
			break;
		}*/
		command->command = spaces_deleter(command->command);
		if (command->command[0] == '\0' && command_number != 0)
			exec_open_pipe_command(command);
		command->command_parts = command_parts_parser(command);
		if (!command->command || !command->command_parts)
		{	
			if (ft_find_char_in_string(string, '|') != -1)
			{
				write(1, "minishell: ", 11);
				write(1, "syntax error near unexpected token `|'\n", 39);
			}
			free(command);
			g_data->error_redirection = FAIL;
			break;
		}
		parser_quote_and_variable(command);
		command_distribution(command);
		command_number += 1;
		clear_data = command;
		command = command->next;
		clear_command_data(clear_data);
		if (g_data->error_command == FAIL)
			break;
	}
	if (g_data->error_redirection != FAIL)
	{
		close(g_data->pipe_array[command_number - 1][1]);
		while (read(g_data->pipe_array[command_number - 1][0], output, 1) > 0)
			write(1, output, 1);
		close(g_data->pipe_array[command_number - 1][0]);	
	}
	//g_data->command_counter = 0;
	set_exit_code(g_data->command_counter);
	g_data->error_command = FALSE;
	g_data->error_redirection = FALSE;
	free_pipe_array();
	free(string);
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
		str = readline(BEGIN(49, 33)"root@mac:# "CLOSE);
		add_history(str);
		if (str)
			minishell(str, envp);
		else
			ctrl_d_exit();
	}
}