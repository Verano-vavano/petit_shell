# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:30:42 by hdupire           #+#    #+#              #
#    Updated: 2023/09/11 12:48:34 by tcharanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./minishell

MAKE=make
MAKE_CLEAN=make clean
MAKE_FCLEAN=make fclean

MANDATORY=./mandatory/
LIBFT=./libft/
TETRIS=./tetris/
PRINTFD=./printfd/

RM=rm -rf

all:
	@${MAKE} -C ${MANDATORY}

bonus:
	@${MAKE_CLEAN} -C ${MANDATORY}

clean:
	@${MAKE_CLEAN} -C ${MANDATORY}
	@${MAKE_CLEAN} -C ${LIBFT}
	@${MAKE_CLEAN} -C ${TETRIS}
	@${MAKE_CLEAN} -C ${PRINTFD}
	@echo "Cleaning complete !"

fclean: clean
	@${RM} ${NAME}
	@${MAKE_FCLEAN} -C ${LIBFT}
	@${MAKE_FCLEAN} -C ${TETRIS}

re: fclean all

.PHONY:bonus
