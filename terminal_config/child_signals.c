/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 20:05:57 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/16 17:47:42 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hdl_child_sigint(int sig)
{	
	(void)sig;
	write(1, "^C\n", 3);
	return ;
}

void	hdl_child_sigquit(int sig)
{	
	(void)sig;
	write(1, "^\\Quit: 3\n", 11);
	return ;
}
