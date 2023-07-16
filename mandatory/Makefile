# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/07/16 12:24:35 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=../minishell

SRCS=shellpticflesh.c	line_comprehension.c	purposer.c\
	 parse_args.c		parse_args_utils.c		spliter.c\
	 char_utils.c		utils.c					cleaning.c\
	 error_manager.c	heredoc.c				builtins/metal_injection.c\
	 more_char_utils.c	builtins/exit_hell.c \
	 execution.c		syntax_checker.c		builtins/echo_des_enfers.c \
	 env.c builtins/env_infernal.c builtins/les_ex_portes_de_lenfer.c env_utils.c \
	 builtins/unset_et_damnation.c				line_expansions.c\
	 tilde_expansion.c	get_tilde.c builtins/cd_mentiel.c builtins/print_working_damnation.c \
	 env_utils2.c		braces_expansion.c		execution_utils.c\
	 get_cmd.c			files.c					get_path.c\
	 redirections.c
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

fclean: clean
	@${RM} ${NAME}
