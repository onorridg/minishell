/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:33:05 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/19 17:48:33 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// allowed alphabet, numbers but not like as first character in name
t_shell_var	*set_variable(char *string, t_shell_var *last_var)	
{
	char		**data;
	t_shell_var *new_var;
	int			i;
	
	data = split(string, '=');
	if (data && !data[2] && ft_strlen(data[i]) <= LINE_MAX - 1)
	{
		if ((data[0][0] >= 65 && data[0][0] <= 90) ||
			(data[0][0] >= 97 && data[0][0] <= 122) || data[0][0] == '_')
		{	
			i = 0;
			while ((data[0][i] >= 'A' && data[0][i] <= 'Z')
				|| (data[0][i] >= 'a' && data[0][i] <= 'z')
				|| data[0][i] == '_'
				|| (data[0][i] >= '0' && data[0][i] <= '9'))
				i++;
			if (!data[0][i])
			{
				new_var->variable = data[0];
				new_var->value = data[1];
				if (last_var)
					last_var->next = new_var;
			}
			else
				print("[!] Incorrect name variable\n");		//change this error to error like in bash
		}
		else
			print("[!] Incorrect name variable\n"); 		//change this error to error like in bash
	}	
	return (new_var);
}