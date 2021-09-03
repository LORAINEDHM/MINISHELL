CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror -Isrcs -Ilibft

NAME		=	minishell

SRCS		=	main.c init.c free.c utils.c quotes.c path.c error.c token_utils.c \
				parsing/token.c parsing/next_token.c parsing/token_struct.c \
				parsing/pipe.c parsing/parsing.c parsing/dollar.c parsing/split.c\
				program/redirections.c program/redirections2.c program/fork.c program/update_var.c\
				commands/builtins.c commands/echo.c  commands/execute.c commands/export_unset.c \
				commands/env.c commands/exit.c commands/pwd.c controls/control.c commands/cd.c \

LFT_SRC		=	./libft

INCLUDES	= 	-L /Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include

LIBFT		=	$(LFT_SRC)/libft.a

OBJ			=	${addprefix srcs/, ${SRCS:.c=.o}}


all:		$(NAME)

$(NAME):	$(OBJ)
		$(MAKE) all -C libft
		$(CC) -lreadline $(INCLUDES) $(OBJ) $(LIBFT) -o minishell

clean:
		rm -f $(OBJ)
		$(MAKE) $@ -C libft

fclean:		clean
		rm -f $(NAME)
		$(MAKE) $@ -C libft

re:			fclean all

.PHONY:		all fclean re
