NAME = pipex

SRCS = pipex.c pipex_path_utils.c pipex_error_utils.c pipex_struct_utils.c \
	   pipex_proccess_utils.c pipex_shell_parser.c pipex_utils.c

SRCS_BONUS = 

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	make -C libft bonus
	${CC} ${OBJS} -I /libft -L libft/. -lft -o ${NAME}

clean:
	make -C libft clean
	${RM} ${OBJS}

fclean: clean
	make -C libft fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
