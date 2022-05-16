/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:14:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 17:56:05 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_mem(char *string)
{	
	char	*new_string;

	new_string = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (!new_string)
		exit(1);
	return (new_string);
}

char	*quote_parse(t_command *command, int i, int j, char quote)
{
	char	*new_string;
	char	*string;

	string = command->command_parts[i];
	new_string = get_mem(string);
	i = 0;
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '"')
		{
			command->quote = TRUE;
			if (quote == 0)
				quote = string[i];
			else if (quote == string[i])
				quote = 0;
			else
				new_string[j++] = string[i];
		}
		else
			new_string[j++] = string[i];
		i++;
	}
	new_string[j] = '\0';
	free(string);
	return (new_string);
}
