/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 20:25:49 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/16 20:49:03 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		shearch_and_replace_backspace(char *string)
{
	int i;
	int left_spaces;
	int	rigth_spaces;
	int search_status;
	char	**parts_string;
	
	i = 0;
	parts_string = ft_split(string, '\\');
	//if (parts_string && parts_string[1])
	//{
		
	//}
	return (0);
}

char	*search_and_replace_variables(char *string)
{
	
}

void	echo_parser(t_command *command)
{
	
}