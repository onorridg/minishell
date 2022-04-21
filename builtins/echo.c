/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:05:07 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/21 14:13:21 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_variable(char *string)
{
	int 	variable_len;
	char	*variable;
	char	*value;
	
	if (string[1] >= '0' && string[1] <= '9')
		return (1);
	variable_len = ft_whitespaces_len(&string[1], FALSE);
	variable_len = ft_char_len(&string[1], TRUE);
	variable = ft_copy_str_len(&string[1], variable_len);
	value = value_to_variable(variable);
	write(1, value, ft_strlen(value));
	free(value);
	return (variable_len);
}


int	ft_echo(t_command *command)
{
	int	i;
	int j;
	int newline;
	int replace_variable;
	char flag;
	
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
		/*while (command->command_parts[j])
		{
			i = 0;
			if(command->command_parts[j][0] == '$' && ft_strlen(command->command_parts[j]) > 1)
				command->command_parts[j] = value_to_variable(command->command_parts[j]);
			write(1, command->command_parts[j], ft_strlen(command->command_parts[j]));
			j++;
			if (command->command_parts[j])
				write(1, " ", 1);	
		}*/
		while(command->command_parts[j])
		{	
			flag = 0;
			i = 0;
			if (command->command_parts[j][i] == '"' || command->command_parts[j][i] == '\'')
				flag = command->command_parts[j][i++];
			replace_variable = TRUE;
			if (flag == '\'')
				replace_variable = FALSE;
			while (command->command_parts[j][i])
			{
				if (command->command_parts[j][i] == '$' && replace_variable)
					i += print_variable(&command->command_parts[j][i]);
				else 
					write(1, &command->command_parts[j][i], 1);
				i++;
				if (command->command_parts[j][i] == flag)
					break;
			}
			j++;
			if (command->command_parts[j])
				write(1, " ", 1);	
		}
		
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}