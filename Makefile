NAME = pipex

SRCS = pipex.c pipex_check_utils.c pipex_fds_utils.c pipex_mem_utils.c pipex_path_utils.c pipex_proccess_utils.c

SRCS_BONUS = pipex_bonus.c pipex_check_utils_bonus.c pipex_fds_utils_bonus.c pipex_mem_utils_bonus.c pipex_path_utils_bonus.c pipex_proccess_utils_bonus.c

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
	${RM} ${BONUS_OBJS}

fclean: clean
	make -C libft fclean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re