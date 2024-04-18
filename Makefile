NAME	= fdf
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	= ../MLX42
LIBFT	= ./libft

HEADERS	= -I ./include -I $(LIBMLX)/include -I ./libft/includes

LIBS	= ${LIBMLX}/build/libmlx42.a -ldl -lglfw \
			-L"/Users/$(USER)/.brew/opt/glfw/lib/" -pthread -lm \
			-L${LIBFT} -lft


SRCS	:= src/main.c \
			src/error_handling.c
OBJS	:= ${SRCS:.c=.o}

all: libs $(NAME)

libs:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo "Building libft library..."
	@${MAKE} -C libft

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build
	@make clean -C libft
	@echo "cleaning"

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft
	@echo "fcleaning"

re: clean all

.PHONY: all, clean, fclean, re, libmlx