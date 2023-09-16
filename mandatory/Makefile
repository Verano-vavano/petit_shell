# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:34:46 by hdupire           #+#    #+#              #
#    Updated: 2023/09/16 17:04:36 by hdupire          ###   ########.fr        #
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
	 history_loader.c	execution_mainloop.c
SRCS_DIR=$(addprefix srcs/, ${SRCS})
DEST=${SRCS_DIR:.c=.o}

INCLUDES=./include/
LIBFT_PATH=../libft/
LIBFT=$(addsuffix libft.a, ${LIBFT_PATH})

TETRIS_PATH=../tetris/
TETRIS=$(addsuffix libtetris.a, ${TETRIS_PATH})

PRINTFD_PATH=../printfd/
PRINTFD=$(addsuffix libprintfd.a, ${PRINTFD_PATH})

RM=rm -f

GCC=gcc
CFLAGS=-Wall -Wextra -Werror -g
LINKERS=-lreadline -lncurses

all:${NAME}

.c.o:
	@${GCC} ${CFLAGS} -I ${INCLUDES} -I ${LIBFT_PATH} -c $< -o ${<:.c=.o}

${NAME}:${DEST}
	@echo "Doing god's work"
	@make -C ${LIBFT_PATH}
	@make -C ${TETRIS_PATH}
	@make -C ${PRINTFD_PATH}
	@${GCC} ${CFLAGS} ${DEST} -o ${NAME} -L${LIBFT_PATH} -lft -L${TETRIS_PATH} -ltetris -L${PRINTFD_PATH} -lprintfd ${LINKERS} ${LIBFT} ${TETRIS} ${PRINTFD}

clean:
	@${RM} ${DEST}

fclean: clean
	@${RM} ${NAME}
