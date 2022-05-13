/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:17:34 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 19:58:09 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_quote(t_split *data, char *string)
{	
	if (string[data->k] == '"' || string[data->k] == '\'')
	{
		if (data->flag == 0)
			data->flag = string[data->k];
		else if (string[data->k] == data->flag)
			data->flag = 0;
	}
}
