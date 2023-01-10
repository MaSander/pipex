NAME	= pipex

SRCS	= pipex.c \
		find_path.c \
		error.c \
		utils/ft_calloc.c \
		utils/ft_strjoin.c \
		utils/ft_free.c \
		utils/ft_split.c \
		utils/ft_split_ignore.c \
		utils/ft_strlen.c \
		utils/ft_strnstr.c \
		utils/ft_strlcat.c \
		utils/ft_strlcpy.c \
		utils/ft_substr.c \
		utils/ft_strdup.c \

OBJS	= ${SRCS:%.c=%.o}
CFLAGS	= -Wall -Wextra -Werror 
CC		= clang -o3

VFLAGS	= --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --log-file=valgring.log

all:	${NAME}

${NAME}:	${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${OBJS}:	%.o: %.c
	${CC} ${CFLAGS} -o $@ -c $<

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME} ./pipex

re:	fclean all

val: 
	valgrind ${VFLAGS} ./pipex infile "cat" "trzero a b" test.txt
