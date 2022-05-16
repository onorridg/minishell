/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_open_pipe_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:42:57 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 17:51:15 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exec_open_pipe_command(t_command *command)
{
	char	*str;

	str = readline("> ");
	if (!str)
		return (1);
	if (!command)
		exit(1);
	command->command = str;
	return (0);
}
