# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/06/28 11:43:19 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=../minishell

SRCS=shellpticflesh.c
SRCS_DIR=$(addprefix srcs/, ${SRCS})
DEST=${SRCS_DIR:.c=.o}

INCLUDES=./include/

RM=rm -f

GCC=gcc
CFLAGS=-Wall -Wextra -Werror

all:${NAME}

.c.o:
	@${GCC} ${CFLAGS} -c -I ${INCLUDES} $< -o ${<:.c=.o}

${NAME}:${DEST}
	@echo "Doing god's work"
	@${GCC} ${CFLAGS} -o ${NAME}

clean:
	@${RM} ${DEST}

fclean:
	@${RM} ${NAME}
