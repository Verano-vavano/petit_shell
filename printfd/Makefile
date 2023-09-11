NAME = ./libprintfd.a
SRCS = ints.c printfd.c strings.c
DEST = $(SRCS:.c=.o)
all: ${NAME}

.c.o:
	cc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

${NAME} : ${DEST};
	ar cr ${NAME} ${DEST}

clean:
	rm -f ${DEST}

fclean: clean
	rm -f ${NAME}

re: fclean all
