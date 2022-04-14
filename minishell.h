/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:29:10 by onorridg          #+#    #+#             */
/*   Updated: 2022/04/14 18:40:35 by onorridg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE   1
# define FALSE  0
# define FAIL   1

# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

# define DIR_MAX    255
# define PATH_MAX   1024

# define BASH	-1
# define ECHO	0
# define CD 	1
# define PWD 	2
# define EXPORT 3
# define UNSET 	4
# define ENV	5
# define D_EXIT	6



#include <unistd.h>             /* pipe, getcwd, chdir */
#include <stdlib.h>             /* malloc, free */
#include <readline/readline.h>  /* readline */
#include <sys/wait.h>           /*  */
#include <signal.h>

///////
#include <string.h>

typedef struct s_command
{
	int		option;
	int		command_name; 				/* echo - 0 , cd - 1, pwd - 2, export - 3, unset - 4, env - 5, exit - 6 */
	char	**data;
	char	**env;
}	t_command;

typedef struct s_data
{
	int			builtins; 				/*builtins(own implementation of commands like echo and etc.) - 0, from bash - 1 */
	t_command	*commands;
}   t_data;

typedef struct s_heredoc
{
	char				*string;
	struct s_heredoc	*next;	
}	t_heredoc;

typedef struct s_split
{
	int		count;
	char	**words;
}	t_split;


typedef int BUILTIN(t_command *data);


int			ft_echo(t_command *com);
int			ft_cd(t_command *com);
int			ft_pwd(t_command *com);
int 		ft_env(t_command *com);

t_heredoc	*heredoc(char *stop);
t_heredoc 	*free_heredoc(t_heredoc *node);
int			builtin_chek(char *builtin);
char    	*get_command_path(char *command);
BUILTIN		**set_ptr_func_to_arr(void);

char		**ft_split(char *string, char ch);
int			split_free(char **words, int count);
char		*ft_strjoin(char *str1, char *str2);
int			ft_strcmp(char *str1, char *str2);
int			ft_strlen(char *str);



#endif
