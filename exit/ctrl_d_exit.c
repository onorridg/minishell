/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:44:19 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/04 16:32:08 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ctrl_d_exit(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
    rl_redisplay();
	write(1, "exit\n", 5);
	exit(0);
}