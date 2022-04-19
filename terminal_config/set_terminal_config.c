/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_teminal_config.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:05:38 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/18 16:54:47 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	hdl(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
    	rl_redisplay();
	}
	return;
}

static void set_signal_configuration(void)
{
	struct sigaction	act;
	sigset_t			set;
	
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = hdl;
	sigemptyset(&set);                                                             
	sigaddset(&set, SIGINT); 
	act.sa_mask = set;
	sigaction(SIGINT, &act, 0);
	signal(SIGQUIT, SIG_IGN);
}

void set_terminal_configuration(void)
{
	struct termios tp;

	if (tcgetattr(STDIN_FILENO, &tp) == -1)
    	exit(1);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &tp) == -1)
    	exit(1);
	set_signal_configuration();
}