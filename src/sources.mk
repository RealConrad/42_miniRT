
# ---------------------------------------------------------------------------- #
#                                 Source Files                                 #
# ---------------------------------------------------------------------------- #

OBJ_DIR			:= ./objs

VPATH			:= ./src/ ./src/parser/ ./src/utils/ ./src/debugging/ ./src/input/
VPATH			+= ./src/free/ ./src/render/ ./src/vec_utils/ ./src/lighting/
VPATH			+= ./src/objects/

SRC				:= main.c

PARSER_SRC		:= parser.c init_scene.c parser_utils.c init_objects.c input_check.c

UTIL_SRC		:= progress_bar.c split_line.c colour_utils.c ft_dabs.c rand.c

FREE_SRC		:= free_objects.c

INPUT_SRC		:= input.c

RENDER_SRC		:= render_scene.c ray_hit.c ray_calculations.c
RENDER_SRC		+= mlx.c anti_aliasing.c cylinder.c

DEBUGGING_SRC	:= t_printing.c

VEC_UTILS_SRC	:= vector_operations.c vector_operations2.c

LIGHTING_SRC	:= amb_light.c lighting.c

OBJECTS_SRC		:= cylinder.c plane.c sphere.c

SRCS			:= $(SRC) $(PARSER_SRC) $(UTIL_SRC) $(DEBUGGING_SRC) $(INPUT_SRC)
SRCS			+= $(FREE_SRC) $(RENDER_SRC) $(VEC_UTILS_SRC) $(LIGHTING_SRC)
SRCS			+= $(OBJECTS_SRC)

OBJS			:= $(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))
