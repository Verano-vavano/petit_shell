# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/09/28 14:41:35 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./minishell

SRCS=shellpticflesh.c\
	 signals.c  error_manager.c  warnings.c\
	 env.c  env_init_utils.c  env_utils.c  env_utils2.c  env_utils3.c\
	 history.c  history_loader.c  history_utils.c\
	 shellptrc.c\
	 prompt.c  prompt_expansions.c  prompt_colors.c\
	 get_home.c  get_username.c  get_hostname.c  get_cwd.c\
	 spliter.c  parse_args.c  parse_args_utils.c\
	 syntax_checker.c  syntax_checkerers.c\
	 line_comprehension.c  purposer.c\
	 heredoc.c\
	 line_expansions.c\
	 braces_expansion.c  braces_coma_expansion.c  braces_coma_expansion_more.c\
	 braces_dots_expansions.c  braces_dots_expansions_more.c\
	 tilde_expansion.c\
	 parameter_expansion.c  param_exp_utils.c\
	 command_substitution.c  command_subst_exec.c  get_output.c\
	 filename_expansion.c  fe_subverif.c  file_check.c  fe_utils.c  lf_utils.c\
	 word_split.c  word_split_utils.c  word_split_merger.c\
	 quote_removal.c\
	 execution.c  execution_mainloop.c  execution_doer.c  execution_utils.c\
	 get_cmd.c  get_path.c  check_path.c\
	 files.c  file_opening.c  redirections.c\
	 builtin_execution.c\
	 builtins/metal_injection.c  builtins/exit_hell.c  builtins/echo_des_enfers.c\
	 builtins/env_infernal.c  builtins/les_ex_portes_de_lenfer.c  builtins/les_ex_portes_de_lutil.c  builtins/unset_et_damnation.c\
	 builtins/cd_mentiel.c  builtins/cd_mentiellement_util.c  builtins/print_working_damnation.c\
	 cleaning.c  utils.c  char_utils.c  more_char_utils.c\
	 math/assign.c math/char_checking.c math/char_checking2.c math/clean_input.c\
	 math/do_math.c math/is_math.c math/math_delete.c math/operations_ll.c\
	 math/operator.c math/utils.c
SRCS_DIR=$(addprefix ./mandatory/srcs/, ${SRCS})
DEST=${SRCS_DIR:.c=.o}
NO_OF_FILES:=$(words $(SRCS))

START=0
LAST_PERCENT=0

define change_bar_color
	if [ $1 -lt 12 ]; then \
		echo -e -n "\\e[0;31m"; \
	elif [ $1 -lt 24 ]; then \
		echo -e -n "\\e[0;33m"; \
	elif [ $1 -lt 36 ]; then \
		echo -e -n "\\e[0;32m"; \
	else \
		echo -e -n "\\e[0;36m"; \
	fi
endef

define move_progress_bar
	@if [ ${START} -eq 0 ]; then \
		echo -e -n "\\e[0;31m"; \
		echo "COMPILING SHELLPTICFLESH"; \
		echo -e -n "\\e[0m["; \
		echo; \
		echo -e -n "\\e[G"; \
		$(eval START = 1) \
	fi
	@echo -e -n "\\e[?25l\\e[1A\\e[G"
	@$(eval COUNT := $(shell bash -c 'echo $$(($(COUNT) + 1))'))
	@$(eval PERCENT := $(shell bash -c 'echo $$(($(COUNT) * 100 / $(NO_OF_FILES)))'))
	@$(eval current := 1)
	@$(eval MAX := $(shell bash -c 'echo $$(($(PERCENT) / 2))'))
	@echo -e -n "\\e[${LAST_PERCENT}C"
	@for i in $$(seq ${LAST_PERCENT} ${MAX}); do\
		$(call change_bar_color, $$i); \
		echo -n "#"; \
	done
	@echo -e -n "\\e[G\\e[51C"
	@echo -e -n "\\e[0m"
	@echo -n "] "
	@if [ "${PERCENT}" -lt 100 ]; then \
		echo -e -n "\\e[3;37m"; \
	else \
		echo -e -n "\\e[1;3;36m"; \
	fi
	@echo "${PERCENT}% | ${COUNT} / ${NO_OF_FILES}"
	@echo -e -n "\\e[0;0m"
	@echo -e -n "\\e[?25h"
	@$(eval LAST_PERCENT = ${MAX})
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

bonus: ${NAME}

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
	@echo -e -n "\\e[?25h\\e[3;33m"
	@${GCC} ${CFLAGS} ${DEST} -o ${NAME} -L${LIBFT_PATH} -lft -L${TETRIS_PATH} -ltetris -L${PRINTFD_PATH} -lprintfd ${LINK_RL} ${LINKERS} ${LIBFT} ${TETRIS} ${PRINTFD}
	@echo -e -n "\e[1;31m"
	@echo "SHELLPTICFLESH COMPILED"
	@echo -e -n "\e[0m"

clean_libft:
	@echo -e -n "\e[0;32m"
	@echo "Cleaning LIBFT..."
	@make clean -s -C ${LIBFT_PATH}
	@echo -e -n "\e[0m"
	@${RM} ${LIBFT}

clean_tetris:
	@echo -e -n "\e[0;32m"
	@echo "Cleaning Tetris..."
	@make -s -C ${TETRIS_PATH}
	@echo -e -n "\e[0m"
	@${RM} ${TETRIS}

clean_printfd:
	@echo -e -n "\e[0;32m"
	@echo "Cleaning Printfd..."
	@make -s -C ${PRINTFD_PATH}
	@echo -e -n "\e[0m"
	@${RM} ${PRINTFD}

clean: clean_libft clean_tetris clean_printfd
	@echo -e -n "\e[0;32m"
	@echo "Cleaning Shellpticflesh..."
	@${RM} ${DEST}
	@echo -e -n "\e[0m"
	@echo "-----"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY:all .c.o clean fclean clean_libft clean_tetris clean_printf
