# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edfreder <edfreder@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/08 22:26:27 by edfreder          #+#    #+#              #
#    Updated: 2025/05/05 17:15:12 by edfreder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS_P1 = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		  ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		  ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		  ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		  ft_atoi.c ft_calloc.c ft_strdup.c \
		  ft_format_c.c ft_format_i_d.c ft_format_p.c ft_format_s.c ft_format_u.c \
		  ft_format_x.c ft_is_valid_conv.c ft_putnbr_base.c ft_putstr.c ft_printf.c

SRCS_P2 = ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
		  ft_striteri.c	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \

SRCS_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			 ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

		  
OBJS = ${SRCS_P1:.c=.o} ${SRCS_P2:.c=.o}

BONUS_OBJS = ${SRCS_BONUS:.c=.o}

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

INCLUDES = -I .

all: ${NAME}

.c.o:
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	ar rcs ${NAME} ${OBJS}

bonus: ${OBJS} ${BONUS_OBJS}
	ar rcs ${NAME} ${OBJS} ${BONUS_OBJS}

clean:
	${RM} ${OBJS} ${BONUS_OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re