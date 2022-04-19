/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_distribution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:14:25 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/19 14:24:45 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int command_distribution(t_command *command)
{
	BUILTIN	**builtin_functions;
	int		builtin_number;
	
	int i = 0;
	
	
	builtin_functions = set_ptr_func_to_arr();
	while(command->command_parts[i])
	{
		printf("%i - |%s|\n", i, command->command_parts[i]);
		i++;
		printf("---------\n");
	}
	printf("#####\n");
	builtin_number = builtin_chek(command->command_parts[0]);
	//printf("builtin number: %i\n", builtin_number);
	if (builtin_number == D_ECHO || builtin_number == D_CD)
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