/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_redirection_parser.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:35:22 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/11 16:51:35 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void split_redirections(t_command *command, int part, int signs)
{	
	
}

void additional_redirection_parser(t_command *command)
{
	int i;
	int signs;
		
	i = 0;
	signs = 1;
	while (command->command_parts[i])
	{
		if (command->command_parts[i][0] == '<')
		{
			if (command->command_parts[i][1] == '<')
				signs = 2;
			split_redirections(command, i, signs);
			signs = 1;
			i = 0;
		}
		else if (command->command_parts[i][0] == '>')
		{
			if (command->command_parts[i][1] == '>')
				signs = 2;
			split_redirections(command, i, signs);
			signs = 1;
			i = 0;	
		}
	}
	
}