/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:33:20 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/15 18:30:41 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int bash(void)
{
	return 0;
}

static int minishell(int com_num, char **words, char **envp)
{	
	t_command *com;
	BUILTIN **builtins_arr;
	
	com = (t_command *)malloc(sizeof(t_command));
	builtins_arr = set_ptr_func_to_arr();
	if (com_num == 0)
	{	
		com->option = 1;
		if (words[1] && ft_strcmp(words[1], "-n"))
			com->option = 0;
	}
	com->env = envp;
	com->data = words;
	builtins_arr[com_num](com);
	free(com);
	return 0;
}

void hdl(int sig)
{
	if (sig == SIGINT)
	{
		//printf("kek\n");
		//printf("\n"); 			// Move to a new line
    	//rl_on_new_line(); 		// Regenerate the prompt on a newline
    	//rl_replace_line("", 0); // Clear the previous text
    	//rl_redisplay();
	}
	return;
}

int main(int ac, char **av, char **envp)
{	
	char 		**words;
	char 		*str;
	int 		command_number;
	int 		exit_status;
	t_heredoc 	*heredoc_data;

	/* 	"ctrl + C" - SIGINT
		"ctrl + \" - SIGQUIT
	??	"ctrl + D" - SIGHUP  */
	
	struct sigaction act;
	sigset_t   set;
	memset(&act, 0, sizeof(act));
	act.sa_handler = hdl;
	sigemptyset(&set);                                                             
	sigaddset(&set, SIGINT); 
	act.sa_mask = set;
	sigaction(SIGINT, &act, 0);
	signal(SIGQUIT, SIG_IGN);

	struct termios tp;
	if (tcgetattr(STDOUT_FILENO, &tp) == -1)
    	printf("1 - tcgetattr\n");
	//tp.c_iflag &= ~BRKINT;
	tp.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDOUT_FILENO, TCSADRAIN, &tp) == -1)
    	printf("2 - tcsetattr\n");

	
	
	exit_status = 1;
	str = NULL;
	heredoc_data = NULL;
	while (TRUE)
    {	
        str = readline("minishell$ ");
		//printf()
		if (str)
		{	
			words = ft_split(str, ' ');
			command_number = builtin_chek(words[0]);
			if (ft_strcmp(words[0], "<<"))
				heredoc_data = heredoc(words[1]);
			if (command_number == D_EXIT)
				exit(0);
				//exit_status = 0;
			else if (command_number != BASH)
				minishell(command_number, words, envp);
			else
				bash();
			free(str);
			//if (heredoc_data)
			//	heredoc_data = free_heredoc(heredoc_data);
			split_free(words, -1);
		}
		else
		{
			write(0, "exit\n", 6); // control + D
			exit(0);
		}
    }
	return 0;
}
