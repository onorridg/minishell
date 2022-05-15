/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:12:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/15 21:16:42 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_err_hdl(t_command *command, char ch, int number, int sign)
{
	if (ch != '\0')
	{
		errno = 255;
		write(1, "exit\n", 6);
		error_handler(command);
		exit(255);
	}
	else
	{
		if (command->command_parts[2])
		{	
			write(1, "exit\n", 6);
			write(1, "minishell: exit: too many arguments\n", 36);
			set_exit_code(1);
			return (1);
		}
		else
		{	
			write(1, "exit\n", 6);
			exit(number * sign);
		}
	}
	return (0);
}

int	get_sign(char ch)
{
	if (ch == '-')
		return (-1);
	return (1);
}

int	ft_exit(t_command *command)
{	
	char	*chr_number;
	int		i;
	int		number;
	int		sign;
	int		pipe;

	number = 0;
	pipe = g_data->pipe_array[command->command_number][1];
	if (command->command_parts[1])
	{
		chr_number = command->command_parts[1];
		i = 0;
		sign = get_sign(chr_number[i]);
		while (chr_number[i] >= '0' && chr_number[i] <= '9')
		{
			number = number * 10 + (chr_number[i] - '0');
			i++;
		}
		exit_err_hdl(command, chr_number[i], number, sign);
	}
	else
	{ 
		write(1, "exit\n", 5);
		exit(0);
	}
	return (0);
}
