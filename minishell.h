/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:29:10 by onorridg          #+#    #+#             */
/*   Updated: 2022/05/03 12:59:41 by onorridg         ###   ########.fr       */
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

# define D_BASH	-1
# define D_ECHO	0
# define D_CD 	1
# define D_PWD 	2
# define D_EXPORT 3
# define D_UNSET 	4
# define D_ENV	5
# define D_EXIT	6


#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground

#include <unistd.h>             		/* pipe, getcwd, chdir */
#include <stdlib.h>             		/* malloc, free */
#include <readline/readline.h>  		/* readline */
#include <readline/history.h>
#include <sys/wait.h>           		/*  */
#include <signal.h>						/*  sigemptyset, sigaddset, sigaction, signal*/
#include <termios.h>					/* tcgetattr, tcsetattr */
#include <limits.h>
#include <errno.h>						/* errno */
#include <string.h> 					/* strerror */
#include <fcntl.h>						/* open */

//////////////////////
#include <string.h> // 					DELETE !!!
//////////////////////

typedef	struct s_command
{	
	int					command_number;
	char				*command;
	char				**command_parts;
	int					last_command;
	int					file_pipe[2];
	int					here_doc;
	struct s_command 	*next;
}	t_command;

typedef struct s_heredoc
{
	char				*string;
	struct s_heredoc	*next;	
}	t_heredoc;

typedef struct s_own_var
{
	char				*variable;
	char				*value;
	struct 	s_own_var	*next;
}	t_own_var;

typedef struct s_envp
{
	char			*variable;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef struct s_data
{	
	int			command_counter;
	int			**pipe_array;
	int			exit_code;
	char		**envp;
	t_envp		*first_envp;
	t_envp		*last_envp;
	t_own_var 	*first_var;
	t_own_var 	*last_var;
}	t_data;


// start configuration
t_data		*g_data;
void		set_terminal_configuration(char **envp);

// builtins
typedef int BUILTIN(t_command *command);

int			ft_echo(t_command *command);
int			ft_cd(t_command *command);
int			ft_export(t_command *command);
int			ft_pwd(t_command *command);
int			ft_unset(t_command *command);
int 		ft_env(t_command *command);
int 		ft_exit(t_command *command);
int 		plug(t_command *command);
void    	set_exit_code(int exit_code);



int			path_command(t_command *command);

// exit
void 		ctrl_d_exit(void);

// parser
t_command	*string_parser(char *string, char **envp);
char		**command_parts_parser(t_command *command);
char		*spaces_deleter(char *string);
char		*value_to_variable(char *string);
char 		*my_getenv(char *variable);
char		*get_own_env(char *string);
char		*quote_deleter(char	*string);
char		*inser_value_to_string(char *string);
void		parser_quote_and_variable(t_command *command);
void		redirections(t_command *command);


/* executor */
int			command_distribution(t_command *command);
int			set_variable(char *string, char **my_data);
void		exec_open_pipe_command(t_command *command);


// utils
//t_heredoc	*heredoc(char *stop);
t_heredoc 	*free_heredoc(t_heredoc *node);
int			builtin_chek(char *builtin);
char    	*get_command_path(t_command *command);
BUILTIN		**set_ptr_func_to_arr(void);
void 		error_handler(t_command *command);
void 		pipe_array(void);
char		**env_generator(void);
char		**alphabet_sort(void);





/* minilib */
char		**ft_split(char *string, char ch);
int			split_free(char **words, int count); 
int			ft_strcmp(char *str1, char *str2);
int			ft_strlen(char *str);
void		*ft_memset(void *b, int c, size_t len);
char		*ft_set_mem_aloc(char *string);
char		*ft_strjoin_path(char *str1, char *str2);
int			ft_find_char_in_string(char *string, char ch);
char		*ft_copy_str_len(char *string, int len);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strjoin(char *s1, char *s2);
int			ft_whitespaces_len(char *string, int flag);
int			ft_char_len(char *string, int flag);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strdup(const char *s);
char		*ft_itoa(int n);
void		*ft_memcpy(void *dst, const void *src, size_t n);








// libreadline
void rl_replace_line();
void rl_clear_history();


// static


#endif
