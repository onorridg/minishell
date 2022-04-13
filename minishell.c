/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:33:20 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/13 19:24:39 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int bash(void)
{
	return 0;
}

static int minishell(int com_num, char **words)
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
	com->data = words;
	builtins_arr[com_num](com);
	free(com);
	return 0;
}

int main(int ac, char **av)
{	
	char 		**words;
	char 		*str;
	int 		command_number;
	int 		exit;
	t_heredoc 	*heredoc_data;

	exit = 1;
	heredoc_data = NULL;
	while (exit)
    {
        str = readline("minishell$ ");
		words = ft_split(str, ' ');
		command_number = builtin_chek(words[0]);
		if (ft_strcmp(words[0], "<<"))
			heredoc_data = heredoc(words[1]);
		if (command_number == EXIT)
			exit = 0;
		else if (command_number != BASH)
			minishell(command_number, words);
		else
			bash();
        free(str);
		if (heredoc_data)
			heredoc_data = free_heredoc(heredoc_data);
		split_free(words, -1);
    }
}
