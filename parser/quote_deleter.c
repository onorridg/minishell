/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_deleter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:15:37 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/25 17:01:39 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quote_deleter(char	*string)
{
	int		string_len;
	char	*new_string;
	int		i;
	int		y;
	
	string_len = ft_strlen(string);
	if ((string[0] == '\'' || string[0] == '"') && string[0] == string[string_len - 1])
	{	
		new_string = (char *)malloc(sizeof(char) * (string_len - 1));
		if (!new_string)
			exit(1);
		i = 0;
		y = 1;
		while (y < string_len - 1)
			new_string[i++] = string[y++];		
		new_string[i] = '\0';
		return (new_string);
	}
	else
		return (NULL);
}
