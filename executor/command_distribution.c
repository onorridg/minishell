/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_distribution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:14:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/23 13:14:54 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int command_distribution(t_command *command)
{
	BUILTIN	**builtin_functions;
	int		builtin_number;
	
	builtin_functions = set_ptr_func_to_arr();
	
	builtin_number = builtin_chek(command->command_parts[0]);
	if(builtin_number == -1)
		return 0;
		
	if (command->command_parts[0] && !command->command_parts[1]
			&& ft_find_char_in_string(command->command_parts[0], '=') != -1)
				set_variable(command->command);
	
	else if (command->command_parts[0])
		builtin_functions[builtin_number](command);
		//printf(RED BLOD"BASH:"CLOSE" %s\n", command->command);
	return (0);
}