
# ---------------------------------------------------------------------------- #
#                                    Config                                    #
# ---------------------------------------------------------------------------- #

NAME			:= miniRT
CC				:= cc
CFLAGS			:= -I./includes -Wall -Wextra -Werror
LINKS			= -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
LINKS			+= -framework Cocoa -framework OpenGL -framework IOKit
LINKS			+= -pthread
LIBFT_DIR		:= ./libraries/libft
LIBFT			:= ./libraries/libft/libft.a
MLX_DIR			:= ./libraries/mlx
MLX				:= ./libraries/mlx/build/libmlx42.a

# ---------------------------------------------------------------------------- #
#                                 Source Files                                 #
# ---------------------------------------------------------------------------- #

OBJ_DIR			:= ./objs
VPATH			:= ./src/

SRC				:= main.c
SRC				+= parser/parser.c parser/objects.c parser/analize.c

SRCS			:= $(SRC)
OBJS			:= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# ---------------------------------------------------------------------------- #
#                                     Rules                                    #
# ---------------------------------------------------------------------------- #

all: .submodules_initialized $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) $(MLX) $(LINKS)
	@echo $(GREEN)"Linking MiniRT"$(DEFAULT);

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	@cd libraries/mlx && cmake -B build && cmake --build build -j4

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: all

nflag: CFLAGS =
nflag: all

.submodules_initialized:
	git submodule init $(LIBFT_DIR)
	git submodule update $(LIBFT_DIR)
	git submodule init $(MLX_DIR)
	git submodule update $(MLX_DIR)
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