/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_deleter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:15:37 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/25 13:53:41 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quote_deleter(char	*string)
{
	int		string_len;
	char	*new_string;
	int		i;
	
	string_len = ft_strlen(string);
	printf("string length %i\n", string_len);
	if ((string[0] == '\'' || string[0] == '"') && string[0] == string[string_len])
	{	
		new_string = (char *)malloc(sizeof(char) * (string_len - 1));
		if (!new_string)
			exit(1);
		i = 0;
		while (string[i + 1] < string_len - 1)
		{
			new_string[i] = string[i + 1];
			i++;
		}			
		new_string[i] = '\0';
		return (new_string);
	}
	else
		return (NULL);
}
