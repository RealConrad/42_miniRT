
# ---------------------------------- Config ---------------------------------- #
NAME			:= minirt
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror -g
INCLUDES		:= -I./includes
LIBFT_DIR		:= libraries/libft
LIBFT			:= $(LIBFT_DIR)/libft.a

# ------------------------------- Source files ------------------------------- #
OBJ_DIR			:= ./objs
VPATH			:= ./src/

SRC				:= main.c

SRCS			:= $(SRC)
OBJS			:= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# ----------------------------------- Rules ---------------------------------- #
all: init-submodules $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

init-submodules:
	@if [ -z "$(shell ls -A $(LIBFT_DIR))" ]; then \
		git submodule init $(LIBFT_DIR); \
		git submodule update $(LIBFT_DIR); \
	fi
clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(LIBFT) $(NAME)