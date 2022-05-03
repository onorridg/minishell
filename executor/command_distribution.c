/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_distribution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:14:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/03 12:04:46 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int command_distribution(t_command *command)
{
	BUILTIN	**builtin_functions;
	int		builtin_number;
	
	if (command->command_parts[0] && ft_strcmp(command->command_parts[0], "$?"))
	{	
		fprintf(stderr, "exit code: %i\n", g_data->exit_code);
		fflush(stderr);
		//display_exit_code(g_data->exit_code);
		//write(1, "\n", 1);
		return (0);
	}
	builtin_functions = set_ptr_func_to_arr();
	builtin_number = builtin_chek(command->command_parts[0]);
	if(builtin_number == -1)
		return 0;
	if (command->command_parts[0] && ft_find_char_in_string(command->command_parts[0], '=') != -1)
	{	//!command->command_parts[1]
		close(g_data->pipe_array[command->command_number][0]);
		close(g_data->pipe_array[command->command_number][1]);
		set_variable(command->command);
	}
	else if (command->command_parts[0])
		builtin_functions[builtin_number](command);
		//printf(RED BLOD"BASH:"CLOSE" %s\n", command->command);
	return (0);
}