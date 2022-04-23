/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_terminal_config.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:05:38 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/23 12:51:12 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int create_envp_list(char **envp)
{
	int 	i;
	t_envp	*swap;
	char	**data;
	t_envp	*first;
	
	i = 0; 
	while (envp[i])
	{
		swap = g_data->last_envp;
		g_data->last_envp = (t_envp *)malloc(sizeof(t_envp));
		if (!g_data->last_envp)
			exit(1);
		data = ft_split(envp[i], '=');
		if (!data)
			exit(1);
		g_data->last_envp->variable = data[0];
		g_data->last_envp->value = data[1];
		g_data->last_envp->next = NULL;
		if (i == 0)
			g_data->first_envp = g_data->last_envp;
		else
			swap->next = g_data->last_envp;
		i++;
	}
	
	return (0);
}

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

void	set_terminal_configuration(char **envp)
{
	struct termios tp;
	if (tcgetattr(STDIN_FILENO, &tp) == -1)
    	exit(1);
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, 0, &tp) == -1)
    	exit(1);
	set_signal_configuration();
	g_data = NULL;
	g_data = (t_data *)malloc(sizeof(t_data));
	if (!g_data)
		exit(1);
	g_data->command_counter = 0;
	g_data->exit_code = 0;
	g_data->envp = envp;
	g_data->first_var = NULL;
	g_data->last_var = NULL;
	create_envp_list(envp);
}	