/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_err_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:20 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 14:38:16 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int display_pipe_err(char *command)
{
	write(1, "minishell: ", 13);
	write(1, "syntax error near unexpected token `|'\n", 39);
	g_data->exit_code = 258;
	set_exit_code(258);
	free(command);
	return(1);
}

int pipe_err_parser(char *command)
{
	int	i;

	i = 0;
	i = ft_whitespaces_len(&command[i], TRUE);
	if (command[i] == '|')
		return (display_pipe_err(command));
	while (command[i] && command[i] != '|')
		i++;
	i++;
	i += ft_whitespaces_len(&command[i], TRUE);
	if (command[i] == '|')
		return (display_pipe_err(command));
	return (0);
}