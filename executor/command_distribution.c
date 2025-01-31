/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_distribution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:14:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 16:08:03 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_distribution(t_command *command)
{
	t_BUILTIN	**builtin_functions;
	int			builtin_number;

	builtin_functions = set_ptr_func_to_arr();
	builtin_number = builtin_chek(command->command_parts[0]);
	if (builtin_number == -1)
	{	
		free(builtin_functions);
		return (0);
	}
	if (command->command_parts[0]
		&& ft_find_char_in_string(command->command_parts[0], '=') != -1)
	{
		close(g_data->pipe_array[command->command_number][0]);
		close(g_data->pipe_array[command->command_number][1]);
		set_variable(command->command);
	}
	else if (command->command_parts[0])
		builtin_functions[builtin_number](command);
	free(builtin_functions);
	return (0);
}
