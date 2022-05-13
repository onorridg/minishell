/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:46:11 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/13 16:45:01 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_exit_code(int exit_code)
{	
	char	**data;

	data = (char **)malloc(sizeof(char *) * 3);
	if (!data)
		exit(1);
	data[0] = ft_strdup("?");
	data[1] = ft_itoa(exit_code);
	data[2] = 0;
	set_env_variable(data);
}
