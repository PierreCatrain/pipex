# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: picatrai <picatrai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/06 16:26:09 by picatrai          #+#    #+#              #
#    Updated: 2023/12/12 17:56:09 by picatrai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = src/main.c src/ft_split.c src/ft_get_path_cmd.c src/free_close_error.c src/child.c
OBJ = ${SRC:.c=.o}
SRC_BONUS = src_bonus/main.c src/ft_split.c src/ft_get_path_cmd.c src_bonus/free_close_error_bonus.c
OBJ_BONUS = ${SRC_BONUS:.c=.o}
INCLUDE = -I include

%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $< ${INCLUDE}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -o ${NAME} ${OBJ}

all: ${NAME}

bonus : ${OBJ_BONUS}
	${CC} ${CFLAGS} -o ${NAME_BONUS} ${OBJ_BONUS}

clean:
	rm -f ${OBJ} ${OBJ_BONUS}

fclean: clean
	rm -f ${NAME} ${NAME_BONUS}

re: fclean all