/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:57:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 18:04:24 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	display_error(int error_number, t_command *command)
{	
	int	pipe;

	pipe = g_data->pipe_array[command->command_number][1];
	write(1, "minishell: ", 11);
	write(1, command->command_parts[0], ft_strlen(command->command_parts[0]));
	if (command->command_parts[1])
	{
		write(1, ": ", 2);
		write(1, command->command_parts[1],
			ft_strlen(command->command_parts[1]));
	}
	write(1, ": ", 2);
	if (errno != 255)
		write(1, strerror(errno), strlen(strerror(errno)));
	else
		write(1, "numeric argument required", 25);
	write(1, "\n", 1);
}

void	error_handler(t_command *command)
{	
	if (errno == EFAULT)
		errno = ENOENT;
	display_error(errno, command);
	g_data->exit_code = errno;
}
