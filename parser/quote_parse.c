/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:14:06 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 21:26:01 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quote_parse(char *string, int i, int j, char quote)
{
	char	*new_string;

	new_string = (char *)malloc(sizeof(char) * (ft_strlen(string) + 1));
	if (!new_string)
		exit(1);
	while (string[i])
	{
		if (string[i] == '\'' || string[i] == '"')
		{
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
