NAME=minishell
CC=cc
HEADER=minishell.h
CFLAGS= #-Wall -Wextra -Werror
MAKEFILE=Makefile
SRCS=main.c\
	terminal_config/set_terminal_config.c\
	builtins/builtins.c\
	builtins/heredoc.c\
	parser/command_utils.c\
	parser/string_parser.c\
	executor/command_distribution.c\
	exit/ctrl_d_exit.c\
	mini_lib/ft_split.c\
	mini_lib/ft_strjoin.c\
	mini_lib/ft_strcmp.c\
	mini_lib/ft_memset.c\
	mini_lib/ft_set_mem_aloc.c
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