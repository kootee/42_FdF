NAME = fdf
CC = cc
BUILD_DIR = build
BIN_DIR = bin
CFLAGS = -Wextra -Wall -Werror -Wunreachable-code -Ofast
DEBUG_FLAGS = -g -fsanitize=address
LIBMLX = MLX42
LIBFT = libft
debug ?= 0

HEADERS	= -I ./include -I ${LIBMLX}/include/MLX42 -I ./libft/include

LIBS	= ${LIBMLX}/build/libmlx42.a -ldl -lglfw \
			-L"/Users/${USER}/.brew/opt/glfw/lib/" -pthread -lm \
			-L${LIBFT} -lft

SRCS	= 	src/main.c \
			src/color_functions.c \
			src/draw_utils.c \
			src/draw.c \
			src/error_handling.c \
			src/fdf_utils.c \
			src/map_projection_utils.c \
			src/map_utils.c \
			src/parse_map_file.c \
			src/projection_matrices.c

OBJS	= ${SRCS:.c=.o}

ifeq (${debug}, 1)
	CFLAGS := ${CFLAGS} ${DEBUG_FLAGS}
else
	CFLAGS := ${CFLAGS}
endif

all: libs ${NAME}

libs:
	@cmake ${LIBMLX} -B ${LIBMLX}/build && make -C ${LIBMLX}/build -j4
	@${MAKE} -C libft

%.o: %.c
	@${CC} ${CFLAGS} -o $@ -c $< ${HEADERS} && printf "Compiling: ${notdir $<}\n"

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBS} ${HEADERS} -o ${NAME}

clean:
	@rm -rf ${OBJS}
	@make clean -C libft
	@echo "cleaning"

fclean: clean
	@rm -rf ${NAME}
	@rm -rf ${LIBMLX}/build
	@make fclean -C libft
	@echo "fcleaning"

re: clean all

.PHONY: all, libs, clean, fclean, re