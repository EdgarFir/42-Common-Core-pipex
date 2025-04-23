NAME = pipex

SRCS = pipex.c

OBJS = ${SRCS:.c=.o}

CC = cc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: ${NAME}

$(NAME): ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM}

fclean: clean

re: fclean all

.PHONY: all clean fclean re