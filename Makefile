# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 16:26:09 by picatrai          #+#    #+#              #
#    Updated: 2024/01/09 22:48:17 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = src/main.c src/ft_split.c src/ft_get_path_cmd.c src/free_close_error.c
OBJ = ${SRC:.c=.o}
SRC_BONUS = src_bonus/main_bonus.c src/ft_split.c src/ft_get_path_cmd.c \
src/free_close_error.c src_bonus/ft_close_pipe_useless.c src_bonus/gnl_utils.c \
src_bonus/gnl.c src_bonus/ft_here_doc_and_open.c src_bonus/utils_bonus.c
OBJ_BONUS = ${SRC_BONUS:.c=.o}
INCLUDE = -I include

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $< ${INCLUDE}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ}

all: ${NAME}

bonus : ${OBJ_BONUS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ_BONUS}

clean:
	rm -f ${OBJ} ${OBJ_BONUS}

fclean: clean
	rm -f ${NAME} ${NAME_BONUS}

re: fclean all