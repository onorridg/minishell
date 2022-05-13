/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_redirection_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 21:05:43 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 21:13:37 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	arr_len(char **command_parts)
{
	int	i;

	i = 0;
	while (command_parts[i])
		i++;
	return (i);
}

int	split_redirection_len(char *string, int i, int count)
{
	while (string[i])
	{
		if ((string[i] == '<' && string[i + 1] == '<')
			|| (string[i] == '>' && string[i + 1] == '>'))
		{
			count += 1;
			i++;
		}
		else if ((string[i] == '<') || (string[i] == '>'))
		{
			count += 1;
			i++;
		}
		else
		{
			while (string[i] && string[i] != '<' && string[i] != '>')
				i++;
			count += 1;
		}
	}
	return (count);
}

int	check_redirection_sign(char *string)
{
	char	chr1;
	char	chr2;

	chr1 = ft_find_char_in_string(string, '<');
	chr2 = ft_find_char_in_string(string, '>');
	if (chr1 != -1 && (ft_strcmp(string, "<") == 0
			&& ft_strcmp(string, "<<") == 0))
		return (1);
	if (chr2 != -1 && (ft_strcmp(string, ">") == 0
			&& ft_strcmp(string, ">>") == 0))
		return (1);
	return (0);
}
