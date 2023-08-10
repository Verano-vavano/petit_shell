# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:30:42 by hdupire           #+#    #+#              #
#    Updated: 2023/08/09 21:04:59 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./minishell

MAKE=make
MAKE_CLEAN=make clean
MAKE_FCLEAN=make fclean

MANDATORY=./mandatory/
BONUS=./bonus/
LIBFT=./libft/
TETRIS=./tetris/

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
	@${MAKE_CLEAN} -C ${TETRIS}
	@echo "Cleaning complete !"

fclean: clean
	@${RM} ${NAME}
	@${MAKE_FCLEAN} -C ${LIBFT}
	@${MAKE_FCLEAN} -C ${TETRIS}

re: fclean all

.PHONY:bonus
