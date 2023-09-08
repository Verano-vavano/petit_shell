# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdupire <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 09:06:31 by hdupire           #+#    #+#              #
#    Updated: 2023/09/08 17:26:48 by hdupire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_strlen.c ft_bzero.c ft_strcmp.c ft_strncmp.c ft_strnstr.c ft_calloc.c ft_strdup.c ft_strndup.c ft_strjoin.c ft_split.c ft_strchr_int.c get_next_line.c free_buffers.c ft_itoa.c ft_atoi.c ft_atol.c is_dgt.c free_char_etoile_etoile.c ft_strreplace.c get_char_array_size.c ft_time.c ft_getpid.c ft_random.c fill_char_etoile.c ft_tolower.c ft_isupper.c concat_multiple.c ft_strchr.c is_valid_num.c ft_ltoa.c ft_strstr.c ft_nanosleep.c char_array_unite.c ft_longlen.c
DEST = $(SRCS:.c=.o)

all: ${NAME}

.c.o:
	@gcc -Wall -Wextra -Werror -c -I ./ $< -o ${<:.c=.o}

${NAME} : ${DEST}
	@ar crs ${NAME} ${DEST}

clean:
	rm -f ${DEST} ${DEST_BONUS}

fclean: clean
	rm -f ${NAME}

re: fclean all
