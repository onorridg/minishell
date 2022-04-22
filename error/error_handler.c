/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:57:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/22 13:49:16 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void display_error(int error_number, t_command *command)
{
	errno = error_number;
	write(1, "minishell: ", 12);
	write(1, command->command_parts[0], ft_strlen(command->command_parts[0]));
	write(1, ": ", 2);
	write(1, command->command_parts[1], ft_strlen(command->command_parts[1]));
	write(1, ": ", 2);
	if (errno != 255)
		write(1, strerror(errno), strlen(strerror(errno)));
	else
		write(1, "numeric argument required", 26);
	write(1, "\n", 1);
}

void error_handler(t_command *command)
{	
	if (errno == EFAULT)
		errno = ENOENT;
	display_error(errno, command);
	g_data->exit_code = errno;
}