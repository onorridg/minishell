/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:05:07 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 17:31:25 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exit_echo(int newline, int *pipes)
{
	if (newline)
		write(pipes[1], "\n", 1);
	close(pipes[1]);
	free(pipes);
	set_exit_code(0);
}

static int	miss_flag(int *j, t_command *command, int *newline)
{
	if (ft_strcmp(command->command_parts[*j], "-n"))
	{
		*j = 2;
		*newline = FALSE;
		while (command->command_parts[*j]
			&& ft_strcmp(command->command_parts[*j], "-n"))
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
			if (ft_strlen(command->command_parts[j]) == 0)
			{
				j++;
				continue ;
			}
			write(pipes[1], command->command_parts[j],
				ft_strlen(command->command_parts[j]));
			if (command->command_parts[++j])
				write(pipes[1], " ", 1);
		}
	}
	exit_echo(newline, pipes);
	return (0);
}
