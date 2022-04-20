/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_distribution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:14:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/20 19:27:44 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int command_distribution(t_command *command)
{
	BUILTIN	**builtin_functions;
	int		builtin_number;
	
	builtin_functions = set_ptr_func_to_arr();
	builtin_number = builtin_chek(command->command_parts[0]);
	if (!command->command_parts[1] && ft_find_char_in_string(command->command_parts[0], '=') != -1)
		set_variable(command->command, 0);
		//printf("[!] set variable\n");
		
	else if (builtin_number == D_ECHO || builtin_number == D_CD || builtin_number == D_UNSET)
	{	
		builtin_functions[builtin_number](command);
	}
	else if (builtin_number != D_BASH)
	{
		if (!command->command_parts[1]) 								// check options
			builtin_functions[builtin_number](command);
		else
			printf("[!] Error options\n");   				// print error message
	}
	else
	{
		printf(RED BLOD"BASH:"CLOSE" %s\n", command->command);
	}
	return 1;
}