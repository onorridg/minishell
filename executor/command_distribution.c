/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_distribution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:14:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/18 19:34:47 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int command_distribution(t_command *command)
{
	BUILTIN	**builtin_functions;
	int		builtin_number;
	
	builtin_functions = set_ptr_func_to_arr();

	builtin_number = builtin_chek(command->command_parts[0]);
	//printf("builtin number: %i\n", builtin_number);
	if (builtin_number == D_ECHO)
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
		printf("BASH: %s\n", command->command);
	}
	return 1;
}