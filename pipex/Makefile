NAME = pipex

SRCS = pipex_m/pipex.c pipex_m/pipex_path_utils.c pipex_m/pipex_error_utils.c pipex_m/pipex_struct_utils.c \
	   pipex_m/pipex_proccess_utils.c pipex_m/pipex_shell_parser.c pipex_m/pipex_utils.c

SRCS_BONUS = pipex_bonus/pipex_bonus.c pipex_bonus/pipex_path_utils_bonus.c pipex_bonus/pipex_error_utils_bonus.c \
	   pipex_bonus/pipex_struct_utils_bonus.c pipex_bonus/pipex_proccess_utils_bonus.c pipex_bonus/pipex_shell_parser_bonus.c \
	   pipex_bonus/pipex_utils_bonus.c pipex_bonus/here_doc_utils_bonus.c

OBJS = ${SRCS:.c=.o}

BONUS_OBJS = ${SRCS_BONUS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	${RM} ${BONUS_OBJS}
	make -C libft bonus
	${CC} ${CFLAGS} ${OBJS} -I /libft -L libft/. -lft -o ${NAME}

bonus: ${BONUS_OBJS}
	${RM} ${OBJS}
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
