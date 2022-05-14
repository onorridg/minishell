/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:44:19 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/14 19:37:37 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_d_exit(void)
{
	free_all_envp();
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	write(1, "exit\n", 6);
	exit(0);
}
