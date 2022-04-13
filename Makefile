NAME=minishell
CC=cc
HEADER=minishell.h
CFLAGS= #-Wall -Wextra -Werror
MAKEFILE=Makefile
SRCS=minishell.c\
	builtins.c\
	command_utils.c\
	heredoc.c\
	ft_split.c\
	ft_strjoin.c\
	ft_strcmp.c
READLINE_FLAGS=-lreadline

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