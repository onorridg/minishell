/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:12:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 15:18:06 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	plug(t_command *command)
{
	printf("[!] PLUG FUNCTION\n");
	return (0);
}

int ft_exit(t_command *command)
{	
	char *chr_number;
	int i;
	int number;
	int	sign;
	int pipe;

	//parser_quote_and_variable(command); 
	pipe = g_data->pipe_array[command->command_number][1];
	if (command->command_parts[1])
	{
		chr_number = command->command_parts[1];
		i = 0;
		sign = 1;
		if (chr_number[i] == '-')
		{
			sign = -1;
			i++;
		}	
		while(chr_number[i] >= '0' && chr_number[i] <= '9')
			number = number * 10 + (chr_number[i++] - '0');
		if (chr_number[i])
		{
			errno = 255;
			error_handler(command);
		}
		else
		{
			if (command->command_parts[2])
			{
				write(1, "minishell: exit: too many arguments\n", 36);
				set_exit_code(1);
				return (1);
			}
			else 
				exit(number * sign);
		}
	}
	write(1, "exit\n", 5);
	exit(0);
	return (0);
}

int ft_pwd(t_command *command)
{	
	int		i;
	char	dir[DIR_MAX];
	int		*pipes;
	
	//pipes = g_data->pipe_array[command->command_number][1];
	pipes = is_redirection(command);
	if (!getcwd(dir, DIR_MAX))
		error_handler(command);
	i = 0;

	while (dir[i])
		write(pipes[1], &dir[i++], 1);
	write(pipes[1], "\n", 1);
	close(pipes[1]);
	set_exit_code(0);
	return 0;
}

int ft_cd(t_command *command)
{	
	int		result;
	char	*home_path;
	
	//parser_quote_and_variable(command);
	if (command->command_parts[1])
		result = chdir(command->command_parts[1]);
	else
	{
		home_path = my_getenv("HOME");
		if (!home_path)
			result = -1;
		else
		{
			result = chdir((const char*)home_path);
			free(home_path);
		}
	}
	if (result == -1)
	{	
		set_exit_code(1);
		error_handler(command);
	}
	else 
		set_exit_code(0);
	return (0);
}