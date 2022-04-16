NAME=minishell
CC=cc
HEADER=minishell.h
CFLAGS= #-Wall -Wextra -Werror
MAKEFILE=Makefile
SRCS=minishell.c\
	builtins.c\
	parser/command_utils.c\
	heredoc.c\
	mini_lib/ft_split.c\
	mini_lib/ft_strjoin.c\
	mini_lib/ft_strcmp.c
READLINE_FLAGS= -lreadline -L/Users/onorridg/.brew/Cellar/readline/8.1.2/lib
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