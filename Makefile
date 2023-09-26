# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/09/26 16:14:31 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./minishell

SRCS=shellpticflesh.c	line_comprehension.c	purposer.c\
	 parse_args.c		parse_args_utils.c		spliter.c\
	 char_utils.c		utils.c					cleaning.c\
	 error_manager.c	heredoc.c				builtins/metal_injection.c\
	 more_char_utils.c	builtins/exit_hell.c \
	 execution.c		syntax_checker.c		builtins/echo_des_enfers.c \
	 env.c builtins/env_infernal.c builtins/les_ex_portes_de_lenfer.c env_utils.c \
	 builtins/unset_et_damnation.c				line_expansions.c\
	 tilde_expansion.c	get_home.c builtins/cd_mentiel.c builtins/print_working_damnation.c \
	 env_utils2.c		braces_expansion.c		execution_utils.c\
	 get_cmd.c			files.c					get_path.c\
	 redirections.c		env_utils3.c			quote_removal.c\
	 builtin_execution.c						warnings.c\
	 signals.c			braces_dots_expansions.c\
	 parameter_expansion.c braces_coma_expansion.c\
	 braces_dots_expansions_more.c				command_substitution.c\
	 filename_expansion.c						history.c\
	 prompt.c			word_split.c			get_output.c\
	 execution_doer.c	lf_utils.c				fe_utils.c\
	 file_check.c		fe_subverif.c			file_opening.c\
	 check_path.c		history_utils.c			param_exp_utils.c\
	 syntax_checkerers.c						word_split_utils.c\
	 to_delete_utils.c	builtins/cd_mentiellement_util.c\
	 env_init_utils.c	prompt_expansions.c		get_username.c\
	 get_hostname.c		get_cwd.c				builtins/les_ex_portes_de_lutil.c\
	 braces_coma_expansion_more.c				command_subst_exec.c\
	 history_loader.c	execution_mainloop.c	word_split_merger.c\
	 shellptrc.c		prompt_colors.c
SRCS_DIR=$(addprefix ./mandatory/srcs/, ${SRCS})
DEST=${SRCS_DIR:.c=.o}
NO_OF_FILES:=$(words $(SRCS))

START=0

define change_bar_color
	if [ $1 -eq 1 ]; then \
		echo -e -n "\e[0;31m"; \
	elif [ $1 -eq 12 ]; then \
		echo -e -n "\e[0;33m"; \
	elif [ $1 -eq 24 ]; then \
		echo -e -n "\e[0;32m"; \
	elif [ $1 -eq 36 ]; then \
		echo -e -n "\e[0;36m"; \
	fi
endef

define move_progress_bar
	@if [ ${START} -eq 0 ]; then \
		echo -e -n "\e[0;31m"; \
		echo "COMPILING SHELLPTICFLESH"; \
		echo -e -n "\e[0m"; \
		echo; \
		echo -e -n "\e[0G"; \
		$(eval START = 1) \
	fi
	@echo -e -n "\e[?25l"
	@$(eval COUNT := $(shell bash -c 'echo $$(($(COUNT) + 1))'))
	@echo -n "${COUNT} / ${NO_OF_FILES}"
	@$(eval PERCENT := $(shell bash -c 'echo $$(($(COUNT) * 100 / $(NO_OF_FILES)))'))
	@echo -e -n "\e[0G\e[1A["
	@$(eval current := 1)
	@$(eval MAX := $(shell bash -c 'echo $$(($(PERCENT) / 2))'))
	@for i in $$(seq 1 50); do\
		$(call change_bar_color, $$i); \
		if [ "$$i" -le "$(MAX)" ]; then \
			echo -n "#"; \
		else \
			echo -n " "; \
		fi \
	done
	@echo -e -n "\e[0m"
	@echo -n "] "
	@if [ "${PERCENT}" -lt 100 ]; then \
		echo -e -n "\e[3;37m"; \
	else \
		echo -e -n "\e[1;3;36m"; \
	fi
	@echo "${PERCENT}%"
	@echo -e -n "\e[0;0m"
	@echo -e -n "\e[?25h"
endef

define max_count
	@$(eval COUNT := $(shell bash -c 'echo $$(($(NO_OF_FILES) - 1))'))
endef

INCLUDES=./mandatory/include/

LIBFT_PATH=./libft/
LIBFT=$(addsuffix libft.a, ${LIBFT_PATH})

TETRIS_PATH=./tetris/
TETRIS=$(addsuffix libtetris.a, ${TETRIS_PATH})

PRINTFD_PATH=./printfd/
PRINTFD=$(addsuffix libprintfd.a, ${PRINTFD_PATH})

RM=rm -f

GCC=gcc
CFLAGS=-Wall -Wextra -Werror -g
LINKERS=-lreadline -lncurses

UNAME_S:=$(shell uname -s)
ifeq (${UNAME_S},Darwin)
	INCLUDE_RL=-I/usr/local/opt/readline/include
	LINK_RL=-L/usr/local/opt/readline/lib
endif

COUNT=0

all: ${NAME}

.c.o:
	@${GCC} ${CFLAGS} -I ${INCLUDES} -I ${LIBFT_PATH} ${INCLUDE_RL} -c $< -o ${<:.c=.o}
	$(call move_progress_bar, COUNT)

${LIBFT}:
	@echo -e -n "\e[3;33m"
	@echo "Compiling LIBFT..."
	@make -s -C ${LIBFT_PATH}

${TETRIS}:
	@echo -e -n "\e[3;34m"
	@echo "Compiling TETRIS..."
	@make -s -C ${TETRIS_PATH}

${PRINTFD}:
	@echo -e -n "\e[3;35m"
	@echo "Compiling PRINTFD..."
	@make -s -C ${PRINTFD_PATH}

${NAME}: ${LIBFT} ${TETRIS} ${PRINTFD} ${DEST}
	@$(call max_count)
	@$(call move_progress_bar, COUNT)
	@echo -e "\e[?25h"
	@echo -e -n "\e[3;33m"
	@${GCC} ${CFLAGS} ${DEST} -o ${NAME} -L${LIBFT_PATH} -lft -L${TETRIS_PATH} -ltetris -L${PRINTFD_PATH} -lprintfd ${LINK_RL} ${LINKERS} ${LIBFT} ${TETRIS} ${PRINTFD}
	@echo -e -n "\e[1;31m"
	@echo "SHELLPTICFLESH COMPILED"

clean:
	@echo -e -n "\e[0;32m"
	@echo "Cleaning Shellpticflesh..."
	@${RM} ${DEST}
	@echo "Cleaning LIBFT..."
	@make -s -C ${LIBFT_PATH}
	@${RM} ${LIBFT}
	@echo "Cleaning Tetris..."
	@make -s -C ${TETRIS_PATH}
	@${RM} ${TETRIS}
	@echo "Cleaning Printfd..."
	@make -s -C ${PRINTFD_PATH}
	@${RM} ${PRINTFD}
	@echo -e -n "\e[0m"
	@echo "-----"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY:all .c.o clean fclean
