# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/08/09 18:02:17 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./libtetris.a

SRCS=tetris.c draw_outside.c loop.c drawing_utils.c input_read.c nexter.c downer.c side_move.c rotate.c rotate_utils.c liner.c liner_utils.c level.c scoring.c get_next.c ugly.c sleepy_time.c ft_simple_ftoa.c
DEST=${SRCS:.c=.o}

RM=rm -f

GCC=gcc
CFLAGS=-Wall -Wextra -Werror -g
LINKERS=-lncurses

all:${NAME}

.c.o:
	@${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${DEST}
	@echo "Doing god's work"
	@ar crs ${NAME} ${DEST}

clean:
	@${RM} ${DEST}

fclean:
	@${RM} ${NAME}

re: fclean all
