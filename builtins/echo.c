/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:05:07 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/20 19:27:53 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_and_replase_variable(char *string)
{
	int 	start;
	int 	stop;
	char 	*variable;
	
	start = ft_find_char_in_string(string, '$');
	if (start == -1)
		return (string);
	return 0;
}


int	ft_echo(t_command *command)
{
	int	i;
	int j;
	int newline;
	
	j = 1;
	newline = TRUE;
	if (command->command_parts[1])
	{
		if (ft_strcmp(command->command_parts[1], "-n"))
		{
			j = 2;
			newline = FALSE;
			while(ft_strcmp(command->command_parts[j], "-n"))
				j++;
		}
		while (command->command_parts[j])
		{
			i = 0;
			if(command->command_parts[j][0] == '$' && ft_strlen(command->command_parts[j]) > 1)
				command->command_parts[j] = value_to_variable(command->command_parts[j]);
			write(1, command->command_parts[j], ft_strlen(command->command_parts[j]));
			j++;
			if (command->command_parts[j])
				write(1, " ", 1);	
		}
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}