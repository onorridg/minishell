/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:05:07 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 14:56:39 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	miss_flag(int *j, t_command *command, int *newline)
{
	if (ft_strcmp(command->command_parts[*j], "-n"))
	{
		*j = 2;
		*newline = FALSE;
		while (command->command_parts[*j] && ft_strcmp(command->command_parts[*j], "-n"))
			*j += 1;
	}
	return (*j);
}

int	ft_echo(t_command *command)
{
	int	j;
	int	newline;
	int	*pipes;
	
	j = 1;
	pipes = is_redirection(command);
	newline = TRUE;
	if (command->command_parts[j])
	{
		j = miss_flag(&j, command, &newline);
		while (command->command_parts[j])
		{
			write(pipes[1], command->command_parts[j], ft_strlen(command->command_parts[j]));
			j++;
			if (command->command_parts[j])
				write(pipes[1], " ", 1);
		}
	}
	if (newline)
		write(pipes[1], "\n", 1);
	close(pipes[1]);
	free(pipes);
	set_exit_code(0);
	return (0);
}
