NAME=minishell

CC=cc

HEADER=minishell.h

CFLAGS= -g -O0 #-fcommon  #-Wall -Wextra -Werror

MAKEFILE=Makefile

SRCS=main.c\
	terminal_config/set_terminal_config.c\
	builtins/builtins.c\
	builtins/echo.c\
	builtins/shell_variable.c\
	builtins/unset_variable.c\
	builtins/export.c\
	builtins/exit_code.c\
	parser/command_utils.c\
	parser/string_parser.c\
	parser/my_getenv.c\
	parser/get_own_env.c\
	parser/get_command_path.c\
	parser/quote_deleter.c\
	parser/redirections.c\
	parser/redirection_utils.c\
	executor/command_distribution.c\
	executor/path_command.c\
	executor/exec_open_pipe_command.c\
	exit/ctrl_d_exit.c\
	exit/free_pipe_array.c\
	error/error_handler.c\
	mini_lib/ft_split.c\
	mini_lib/ft_strjoin_path.c\
	mini_lib/ft_strjoin.c\
	mini_lib/ft_strcmp.c\
	mini_lib/ft_memset.c\
	mini_lib/ft_set_mem_aloc.c\
	mini_lib/ft_find_chr_in_string.c\
	mini_lib/ft_copy_str_len.c\
	mini_lib/ft_strlcpy.c\
	mini_lib/ft_whitespaces_len.c\
	mini_lib/ft_char_len.c\
	mini_lib/pipe_array.c\
	mini_lib/env_generator.c\
	mini_lib/ft_strlen.c\
	mini_lib/replace_varibale_in_string.c\
	mini_lib/alphabet_sort.c\
	mini_lib/ft_memcmp.c\
	mini_lib/ft_memcpy.c\
	mini_lib/ft_strdup.c\
	mini_lib/ft_itoa.c

READLINE_FLAGS= -lreadline -L/Users/onorridg/.brew/opt/readline/lib

OBJS=$(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(READLINE_FLAGS)

%.o: %.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re