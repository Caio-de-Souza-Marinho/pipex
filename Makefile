NAME		= pipex
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
RM		= rm -rf

SRC_DIR		= ./
OBJ_DIR		= obj/
INCLUDE		= -I .
LIBFT_DIR	= libft/
LIBFT_LIB	= ${LIBFT_DIR}libft.a
TEST_FILE1	= input.txt
TEST_FILE2	= output.txt
CMD_1		= "catt"
CMD_2		= "wc -l"

SRCS		= $(SRC_DIR)main.c \
		  ${SRC_DIR}errors.c \
		  ${SRC_DIR}init.c \
		  ${SRC_DIR}parse_args.c \
		  ${SRC_DIR}close.c \

OBJS		= ${SRCS:${SRC_DIR}%.c=${OBJ_DIR}%.o}

all:		${OBJ_DIR} ${NAME}

${NAME}:	${OBJS} ${LIBFT_LIB}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT_LIB} ${INCLUDE} -o ${NAME}

${OBJ_DIR}:
			@mkdir -p ${OBJ_DIR}

${OBJ_DIR}%.o:	${SRC_DIR}%.c
			@mkdir -p ${OBJ_DIR}
			${CC} ${CFLAGS} -I . -I ${LIBFT_DIR} -c $< -o $@

${LIBFT_LIB}:
			@echo "Building libft..."
			make -C ${LIBFT_DIR}

leakfull:
			valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./${NAME} ${TEST_FILE1} ${CMD_1} ${CMD_2} ${TEST_FILE2}

clean:
			@echo "Cleaning object files..."
			${RM} ${OBJ_DIR}
			@echo "Cleaning libft objects..."
			make clean -C ${LIBFT_DIR}

fclean:		clean
			@echo "Removing binary and libraries..."
			${RM} ${NAME}
			make fclean -C ${LIBFT_DIR}

re:		fclean all

.PHONY:		all clean fclean re
