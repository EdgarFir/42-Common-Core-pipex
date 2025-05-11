NAME = pipex

SRCS = pipex.c pipex_path_utils.c pipex_error_utils.c pipex_struct_utils.c \
	   pipex_proccess_utils.c pipex_shell_parser.c pipex_utils.c

SRCS_BONUS = pipex_bonus.c pipex_path_utils_bonus.c pipex_error_utils_bonus.c pipex_struct_utils_bonus.c \
	   pipex_proccess_utils_bonus.c pipex_shell_parser_bonus.c pipex_utils_bonus.c here_doc_utils_bonus.c

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: ${NAME}

.c.o:
	${CC} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	make -C libft bonus
	${CC} ${CFLAGS} ${OBJS} -I /libft -L libft/. -lft -o ${NAME}

bonus: ${BONUS_OBJS}
	make -C libft bonus
	${CC} ${CFLAGS} ${BONUS_OBJS} -I /libft -L libft/. -lft -o ${NAME}

clean:
	make -C libft clean
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	make -C libft fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
