/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_err_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 14:04:20 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/14 21:16:36 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	display_pipe_err(char *command)
{
	write(1, "minishell: ", 12);
	write(1, "syntax error near unexpected token `|'\n", 39);
	g_data->exit_code = 258;
	set_exit_code(258);
	free(command);
	return (1);
}

static void	quote_setter(char *command, int i, char *quote)
{
	if (command[i] && (command[i] == '\'' || command[i] == '"'))
	{
		if (*quote == 0)
			*quote = command[i];
		else if (*quote == command[i])
			*quote = 0;
	}
}

int	pipe_err_parser(char *command)
{
	int		i;
	char	quote;

	quote = 0;
	i = 0;
	i = ft_whitespaces_len(command, TRUE);
	if (command[i] && command[i] == '|')
		return (display_pipe_err(command));
	while (command[i])
	{
		while (command[i] && command[i] != '|')
		{	
			quote_setter(command, i, &quote);
			i++;
		}
		if (command[i])
			i++;
		if (command[i])
		{
			i += ft_whitespaces_len(&command[i], TRUE);
			if (command[i] && command[i] == '|' && quote == 0)
				return (display_pipe_err(command));
		}
	}
	return (0);
}
