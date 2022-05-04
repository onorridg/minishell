/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:46:11 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/04 11:57:37 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    set_exit_code(int exit_code)
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
