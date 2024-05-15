NAME	= fdf
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g -fsanitize=address
LIBMLX	= MLX42
LIBFT	= libft
debug	?= 0

HEADERS	= -I ./include -I ${LIBMLX}/include/MLX42 -I ./libft/include

LIBS	= ${LIBMLX}/build/libmlx42.a -ldl -lglfw \
			-L"/Users/${USER}/.brew/opt/glfw/lib/" -pthread -lm \
			-L${LIBFT} -lft

SRCS	= ${wildcard src/*.c}

OBJS	= ${SRCS:.c=.o}

all: libs $(NAME)

libs:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@${MAKE} -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@make clean -C libft
	@echo "cleaning"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)/build
	@make fclean -C libft
	@echo "fcleaning"

re: clean all

.PHONY: all, clean, fclean, re, libmlx