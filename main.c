/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:19:51 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/18 16:07:16 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void hdl(int sig)
{
	if (sig == SIGINT)
	{
		//printf("kek\n");
		//printf("\n"); 			// Move to a new line
    	/*rl_on_new_line(); 		// Regenerate the prompt on a newline
    	rl_replace_line("", 0); // Clear the previous text
    	rl_redisplay();*/
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
    	rl_redisplay();
	}
	return;
}

int main(int ac, char **av, char **envp)
{
	char *str;
	struct termios tp;

	
	if (tcgetattr(STDIN_FILENO, &tp) == -1)
    	exit(1);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &tp) == -1)
    	exit(1);
	struct sigaction act;
	sigset_t   set;
	memset(&act, 0, sizeof(act));
	act.sa_handler = hdl;
	sigemptyset(&set);                                                             
	sigaddset(&set, SIGINT); 
	act.sa_mask = set;
	sigaction(SIGINT, &act, 0);
	signal(SIGQUIT, SIG_IGN);
	str = NULL;
	while (1)
	{
		str = readline(BEGIN(49, 31)"root@mac:# "CLOSE);
		add_history(str);
		if (!str)
		{	
			//fflush(stdout);
			//write(1, "")
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			write(1, "exit\n", 5);
			break;
		}
		free(str);
	}
}