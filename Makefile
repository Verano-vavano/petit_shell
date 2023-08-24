# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:30:42 by hdupire           #+#    #+#              #
#    Updated: 2023/08/24 18:13:26 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./minishell

MAKE=make
MAKE_CLEAN=make clean
MAKE_FCLEAN=make fclean

MANDATORY=./mandatory/
LIBFT=./libft/
TETRIS=./tetris/

RM=rm -rf

all:
	@${MAKE} -C ${MANDATORY}

bonus:
	@${MAKE_CLEAN} -C ${MANDATORY}

clean:
	@${MAKE_CLEAN} -C ${MANDATORY}
	@${MAKE_CLEAN} -C ${LIBFT}
	@${MAKE_CLEAN} -C ${TETRIS}
	@echo "Cleaning complete !"

fclean: clean
	@${RM} ${NAME}
	@${MAKE_FCLEAN} -C ${LIBFT}
	@${MAKE_FCLEAN} -C ${TETRIS}

re: fclean all

.PHONY:bonus
