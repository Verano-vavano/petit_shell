# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:30:42 by hdupire           #+#    #+#              #
#    Updated: 2023/06/29 16:05:41 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./minishell

MAKE=make
MAKE_CLEAN=make clean

MANDATORY=./mandatory/
BONUS=./bonus/
LIBFT=./libft/

RM=rm -rf

all:
	@${MAKE_CLEAN} -C ${BONUS}
	@${MAKE} -C ${MANDATORY}

bonus:
	@${MAKE_CLEAN} -C ${MANDATORY}
	@${MAKE} -C ${BONUS}

clean:
	@${MAKE_CLEAN} -C ${MANDATORY}
	@${MAKE_CLEAN} -C ${BONUS}
	@${MAKE_CLEAN} -C ${LIBFT}
	@echo "Cleaning complete !"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY:bonus
