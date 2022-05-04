/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:05:07 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/04 11:44:32 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_variable(int command_number, char *string)
{
	int		variable_len;
	char	*variable;
	char	*value;

	//variable_len = ft_whitespaces_len(&string[1], FALSE);
	if (ft_strcmp(string, "$?"))
		variable_len = 1;
	else
		variable_len = ft_char_len(&string[1], TRUE);
	variable = ft_copy_str_len(&string[1], variable_len);
	value = value_to_variable(variable);
	write(g_data->pipe_array[command_number][1], value, ft_strlen(value));
	free(value);
	return (variable_len);
}

int	miss_flag(int *j, t_command *command, int *newline)
{
	if (ft_strcmp(command->command_parts[*j], "-n"))
	{
		*j = 2;
		*newline = FALSE;
		while (ft_strcmp(command->command_parts[*j], "-n"))
			*j += 1;
	}
	return (*j);
}

void	quotes(int command_number, char ch, char *flag, int *replace_variable)
{
	if (*flag == 0)
		*flag = ch;
	else if (ch == *flag)
		*flag = 0;
	else
		write(g_data->pipe_array[command_number][1], &ch, 1);
	if (*flag == '"' || *flag == 0)
		*replace_variable = TRUE;
	else
		*replace_variable = FALSE;
}

void	print_one_word(int command_number, char *word, char flag, int i)
{
	int	replace_variable;

	replace_variable = TRUE;
	if (flag == '\'')
		replace_variable = FALSE;
	while (word[i])
	{	
		if (word[i] == '"' || word[i] == '\'')
			quotes(command_number,word[i], &flag, &replace_variable);
		else if (word[i] == '$' && replace_variable)
			i += print_variable(command_number, &word[i]);
		else
			write(g_data->pipe_array[command_number][1], &word[i], 1);
		i++;
		if (!word[i + 1] && word[i] == flag)
			break ;
	}	
}

int	ft_echo(t_command *command)
{
	int	j;
	int	newline;

	j = 1;
	newline = TRUE;
	if (command->command_parts[j])
	{
		j = miss_flag(&j, command, &newline);
		while (command->command_parts[j])
		{
			print_one_word(command->command_number, command->command_parts[j], 0, 0);
			j++;
			if (command->command_parts[j])
				write(g_data->pipe_array[command->command_number][1], " ", 1);
		}
	}
	if (newline)
		write(g_data->pipe_array[command->command_number][1], "\n", 1);
	return (0);
}
