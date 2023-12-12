
# ---------------------------------- Config ---------------------------------- #
NAME			:= minirt
CC				:= cc
CFLAGS			:= -I./includes -Wall -Wextra -Werror -g
LIBFT_DIR		:= libraries/libft
LIBFT			:= libraries/libft/libft.a

# ------------------------------- Source files ------------------------------- #
OBJ_DIR			:= ./objs
VPATH			:= ./src/

SRC				:= main.c

SRCS			:= $(SRC)
OBJS			:= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# ----------------------------------- Rules ---------------------------------- #
all: .submodules_initialized $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo $(GREEN)"Linking MiniRT"$(DEFAULT);

$(LIBFT):
	make -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.submodules_initialized:
	git submodule init $(LIBFT_DIR)
	git submodule update $(LIBFT_DIR)
	@touch .submodules_initialized

clean:
	rm -rf $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) .submodules_initialized

re: fclean all

.PHONY: all clean fclean re

# Colours to make it look nice :)
DEFAULT	= "\033[39m"
GREEN	= "\033[32m"