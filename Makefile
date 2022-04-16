NAME=minishell
CC=cc
HEADER=minishell.h
CFLAGS= #-Wall -Wextra -Werror
MAKEFILE=Makefile
SRCS=minishell.c\
	builtins.c\
	command_utils.c\
	heredoc.c\
	minilib/ft_split.c\
	minilib/ft_strjoin.c\
	minilib/ft_strcmp.c
READLINE_FLAGS=-lreadline -L/Users/onorridg/.brew/Cellar/readline/8.1.2/lib #-I/Users/onorridg/.brew/Cellar/readline/8.1.2/include

OBJS=$(SRCS:.c=.o)

all:$(NAME)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(READLINE_FLAGS)

%.o: %.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re