/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:08:48 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/14 14:49:27 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	config_and_pars(t_command *command, char *string, int command_number)
{
	g_data->error_redirection = FALSE;
	g_data->error_command = FALSE;
	command->command_number = command_number;
	command->command = spaces_deleter(command->command);
	if (command && command->command[0] == '\0' && command_number != 0
		&& !command->next)
		exec_open_pipe_command(command);
	command->command_parts = command_parts_parser(command);
	if (cpp_err_hdl(command, string))
		return (1);
	parser_quote_and_variable(command);
	if (pqv_err_hdl(command, string))
		return (1);
	return (0);
}

void	display_pipe_data(int command_number)
{	
	char	*output[1];

	if (g_data->error_redirection != FAIL)
	{
		close(g_data->pipe_array[command_number - 1][1]);
		while (read(g_data->pipe_array[command_number - 1][0], output, 1) > 0)
			write(1, output, 1);
		close(g_data->pipe_array[command_number - 1][0]);
	}
}

int	cpp_err_hdl(t_command *command, char *string)
{
	if (!command->command || !command->command_parts)
	{	
		if (ft_find_char_in_string(string, '|') != -1)
		{
			write(1, "minishell: syntax error: unexpected end of file\n", 48);
			g_data->exit_code = 258;
			set_exit_code(258);
		}
		clear_command_data(command);
		g_data->error_redirection = FAIL;
		return (1);
	}
	return (0);
}

int	pqv_err_hdl(t_command *command, char *string)
{
	if (!command->command || !command->command_parts
		|| !command->command_parts[0])
	{	
		if (ft_find_char_in_string(string, '|') != -1)
		{
			write(1,
				"minishell: syntax error near unexpected token `newline'\n",
				56);
			g_data->exit_code = 258;
			set_exit_code(258);
		}
		clear_command_data(command);
		g_data->error_redirection = FAIL;
		return (1);
	}
	return (0);
}
