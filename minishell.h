/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onorridg <onorridg@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 17:29:10 by onorridg          #+#    #+#             */
/*   Updated: 2022/12/19 13:04:07 by onorridg         ###   ########.fr       */
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

# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>

typedef struct s_command
{	
	int					command_number;
	char				*command;
	char				**command_parts;
	int					last_command;
	int					file_pipe[2];
	int					here_doc;
	int					quote;
	struct s_command	*next;
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
	struct s_own_var	*next;
}	t_own_var;

typedef struct s_envp
{
	char			*variable;
	char			*value;
	struct s_envp	*next;
}	t_envp;

typedef int	t_BUILTIN(t_command *command);

typedef struct s_data
{
	int			error_redirection;
	int			error_command;
	int			command_counter;
	int			**pipe_array;
	int			exit_code;
	int			command_count;
	char		**envp;
	t_envp		*first_envp;
	t_envp		*last_envp;
	t_own_var	*first_var;
	t_own_var	*last_var;
}	t_data;

typedef struct s_split
{
	int		word_len;
	int		i;
	int		j;
	int		k;
	char	flag;
}	t_split;

t_data		*g_data;
/* start configuration */
void		set_terminal_configuration(char **envp);

/* builtins */

int			ft_echo(t_command *command);
int			ft_cd(t_command *command);
int			ft_export(t_command *command);
int			ft_pwd(t_command *command);
int			ft_unset(t_command *command);
int			ft_env(t_command *command);
int			ft_exit(t_command *command);
void		set_exit_code(int exit_code);
int			get_envp(char **data);
int			get_own_envp(char **data, char *variable);
int			set_new_env_entry(char *variable, char *value);
int			set_my_env_variable(char **data);

int			path_command(t_command *command);

/* exit */
void		ctrl_d_exit(char *str);

/* parser */
t_command	*string_parser(char *string, char **envp);
char		**command_parts_parser(t_command *command);
char		*spaces_deleter(char *string);
char		*value_to_variable(char *string);
char		*my_getenv(char *variable);
char		*get_own_env(char *string);
char		*inser_value_to_string(char *str, int i, char quote, char *val);
void		parser_quote_and_variable(t_command *command);
void		redirections(t_command *command);
char		*quote_parse(t_command *command, int i, int j, char quote);
int			*is_redirection(t_command *command);
int			pipe_err_parser(char *command);
void		additional_redirection_parser(t_command *command);
void		free_replace_variable(char *new_string, char *left_part,
				char *value, char *right_part);
int			set_qoute_replace_variable(char *quote, char *str, int i);
int			check_redirection_sign(char *string);
int			split_redirection_len(char *string, int i, int count);
int			arr_len(char **command_parts);
void		heredoc_read(char *stop, int pipe_write);

/* executor */
int			command_distribution(t_command *command);
int			set_variable(char *string);
int			set_env_variable(char **data);
int			exec_open_pipe_command(t_command *command);
void		set_pipe_config(t_command *command, int *pipe_fds);
void		get_status_code(int stt, char *path, t_command *command);
void		get_status_code_signal(int stt);
void		set_fork_signal(int flag);
void		close_fork_pipe(t_command *command, int *pipe_fds);

/* utils */
t_heredoc	*free_heredoc(t_heredoc *node);
int			builtin_chek(char *builtin);
char		*get_command_path(t_command *command);
t_BUILTIN	**set_ptr_func_to_arr(void);
void		error_handler(t_command *command);
void		pipe_array(void);
char		**env_generator(void);
char		**alphabet_sort(void);
void		error_redirection_handler(t_command *command, char *file_n);
void		rewrite_command_part_arr(t_command *command, int part);
void		get_pipe(t_command *command, int flag);
void		set_signal_configuration(void);
void		free_pipe_array(void);
void		hdl_child_sigint(int sig);
void		hdl_child_sigquit(int sig);
int			pqv_err_hdl(t_command *command, char *string);

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
void		is_quote(t_split *data, char *string);
void		clear_command_data(t_command *command);
int			cpp_err_hdl(t_command *command, char *string);
void		display_pipe_data(int command_number);
int			config_and_pars(t_command *command, char *string,
				int command_number);
void		free_all_envp(void);

void		rl_replace_line(const char *text, int clear_undo);

#endif
