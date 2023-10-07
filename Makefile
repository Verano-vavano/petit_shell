# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/10/07 15:22:57 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=./minishell

SRCS=shellpticflesh.c  shellpticflesh_more.c\
	 signals.c  error_manager.c  warnings.c\
	 env.c  env_init_utils.c  env_utils.c  env_utils2.c  env_utils3.c\
	 history.c  history_loader.c  history_utils.c\
	 var_assign.c\
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
	 builtins/print_formated_hell.c\
	 builtins/env_infernal.c  builtins/les_ex_portes_de_lenfer.c  builtins/les_ex_portes_de_lutil.c  builtins/unset_et_damnation.c\
	 builtins/cd_mentiel.c  builtins/cd_mentiellement_util.c  builtins/print_working_damnation.c\
	 builtins/hellias.c  builtins/hellias_sort.c builtins/hellias_print.c\
	 alias_expansion.c  alias_utils.c  builtins/unhellias.c\
	 builtins/source_of_styx.c\
	 builtins/printf/printferno.c  builtins/printf/printf_arg_modifier.c\
	 builtins/printf/format_arg.c  builtins/printf/printf_init_helper.c\
	 builtins/printf/printf_modifier_utils.c  builtins/printf/printf_loop.c\
	 builtins/beastory.c  builtins/beastory_print.c\
	 cleaning.c  utils.c  char_utils.c  more_char_utils.c  word_utils.c\
	 is_quoted.c\
	 math/assign.c math/char_checking.c math/char_checking2.c math/clean_input.c\
	 math/do_math.c math/is_math.c math/math_delete.c math/operations_ll.c\
	 math/operator.c math/utils.c
SRCS_DIR=$(addprefix ./mandatory/srcs/, ${SRCS})
DEST=${SRCS_DIR:.c=.o}
NO_OF_FILES:=$(words $(SRCS))

START=0
LAST_PERCENT=0

RED=$(shell tput setaf 1)
GREEN=$(shell tput setaf 2)
YELLOW=$(shell tput setaf 3)
BLUE=$(shell tput setaf 4)
MAGENTA=$(shell tput setaf 5)
CYAN=$(shell tput setaf 6)
WHITE=$(shell tput setaf 7)
RESET=$(shell tput sgr0)

HIDE_CURSOR=$(shell tput civis)
SHOW_CURSOR=$(shell tput cnorm)
CURSOR_UP=$(shell tput cuu1)
CURSOR_DOWN=$(shell tput cud1)
BEG_LINE=$(shell tput hpa 0)
BOLD=$(shell tput bold)

define change_bar_color
	if [ $1 -lt 12 ]; then \
		printf "${RED}"; \
	elif [ $1 -lt 24 ]; then \
		printf "${YELLOW}"; \
	elif [ $1 -lt 36 ]; then \
		printf "${GREEN}"; \
	else \
		printf "${CYAN}"; \
	fi
endef

define move_progress_bar
	@if [ ${START} -eq 0 ]; then \
		printf "${MAGENTA}"; \
		echo "COMPILING SHELLPTICFLESH"; \
		printf "${RESET}"; \
		tput cud1; \
		$(eval START = 1) \
	fi
	@tput civis; tput cuu1; tput hpa 0
	@$(eval COUNT := $(shell bash -c 'echo $$(($(COUNT) + 1))'))
	@$(eval PERCENT := $(shell bash -c 'echo $$(($(COUNT) * 100 / $(NO_OF_FILES)))'))
	@$(eval current := 1)
	@$(eval MAX := $(shell bash -c 'echo $$(($(PERCENT) / 2))'))
	@printf "["
	@tput hpa 0
	@tput cuf ${LAST_PERCENT}
	@for i in $$(seq ${LAST_PERCENT} ${MAX}); do\
		$(call change_bar_color, $$i); \
		printf "#"; \
	done
	@tput hpa 0; tput cuf 51
	@printf "${RESET}"
	@printf "] "
	@if [ "${PERCENT}" -lt 100 ]; then \
		printf "${WHITE}"; \
	else \
		printf "${CYAN}${BOLD}"; \
	fi
	@echo "${PERCENT}% | ${COUNT} / ${NO_OF_FILES}"
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
	DEFINE_OS='OS="darwin"'
else
	DEFINE_OS='OS="linux"'
endif

COUNT=0

all: ${NAME}

bonus: ${NAME}

.c.o:
	@${GCC} ${CFLAGS} -D${DEFINE_OS} -I ${INCLUDES} -I ${LIBFT_PATH} ${INCLUDE_RL} -c $< -o ${<:.c=.o}
	$(call move_progress_bar, COUNT)

${LIBFT}:
	@echo "${RED}Compiling LIBFT..."
	@make -s -C ${LIBFT_PATH}
	@printf "${RESET}"

${TETRIS}:
	@echo "${BLUE}Compiling TETRIS..."
	@make -s -C ${TETRIS_PATH}
	@printf "${RESET}"

${PRINTFD}:
	@echo "${YELLOW}Compiling PRINTFD..."
	@make -s -C ${PRINTFD_PATH}
	@printf "${RESET}"

${NAME}: ${LIBFT} ${TETRIS} ${PRINTFD} ${DEST}
	@$(call max_count)
	@$(call move_progress_bar, COUNT)
	@${GCC} ${CFLAGS} ${DEST} -o ${NAME} -L${LIBFT_PATH} -lft -L${TETRIS_PATH} -ltetris -L${PRINTFD_PATH} -lprintfd ${LINK_RL} ${LINKERS} ${LIBFT} ${TETRIS} ${PRINTFD}
	@printf "${GREEN}${BOLD}"
	@echo "SHELLPTICFLESH COMPILED"
	@printf "${RESET}"
	@printf ${SHOW_CURSOR}

clean_libft:
	@echo "${GREEN}Cleaning LIBFT..."
	@make clean -s -C ${LIBFT_PATH}
	@printf "${RESET}"
	@${RM} ${LIBFT}

clean_tetris:
	@echo "${GREEN}Cleaning Tetris..."
	@make -s -C ${TETRIS_PATH}
	@printf "${RESET}"
	@${RM} ${TETRIS}

clean_printfd:
	@echo "${GREEN}Cleaning Printfd..."
	@make -s -C ${PRINTFD_PATH}
	@printf "${RESET}"
	@${RM} ${PRINTFD}

clean: clean_libft clean_tetris clean_printfd
	@echo "${GREEN}Cleaning Shellpticflesh..."
	@${RM} ${DEST}
	@printf "${RESET}"
	@echo "~~~~"

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY:all .c.o clean fclean clean_libft clean_tetris clean_printf
