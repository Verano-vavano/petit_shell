# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/07/04 18:00:39 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=../minishell

SRCS=shellpticflesh.c	line_comprehension.c	purposer.c\
	 parse_args.c		parse_args_utils.c		spliter.c\
	 char_utils.c		utils.c					cleaning.c\
	 error_manager.c	heredoc.c				metal-injection.c
SRCS_DIR=$(addprefix srcs/, ${SRCS})
DEST=${SRCS_DIR:.c=.o}

INCLUDES=./include/
LIBFT_PATH=../libft/
LIBFT=$(addsuffix libft.a, ${LIBFT_PATH})

RM=rm -f

GCC=gcc
CFLAGS=-Wall -Wextra -Werror -g
LINKERS=-lreadline

all:${NAME}

.c.o:
	@${GCC} ${CFLAGS} -c -I ${INCLUDES} -I ${LIBFT_PATH} $< -o ${<:.c=.o}

${NAME}:${DEST}
	@echo "Doing god's work"
	@make -C ${LIBFT_PATH}
	@${GCC} ${CFLAGS} ${LINKERS} ${LIBFT} ${DEST} -o ${NAME}

clean:
	@${RM} ${DEST}

fclean:
	@${RM} ${NAME}
