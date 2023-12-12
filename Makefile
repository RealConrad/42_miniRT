
# ---------------------------------- Config ---------------------------------- #
NAME			:= minirt
CC				:= cc
CFLAGS			:= -I./includes -Wall -Wextra -Werror -g
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

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

init-submodules:
	@git submodule init $(LIBFT_DIR)
	@git submodule update $(LIBFT_DIR)

clean:
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re $(NAME)