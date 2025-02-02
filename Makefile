NAME		=	cub3D
BNS_NAME	=	cub3D_bonus
CC			= 	cc
CFLAGS		=	-Wall -Wextra -Werror -Iincludes -I./includes/ -fsanitize=address -g3

SRC			=	cub/cub.c cub/src/parsing/init_map.c \
				cub/src/parsing/init_elements.c cub/src/parsing/parsing.c \
				cub/src/rendering/hooks.c cub/src/rendering/raycasting.c \
				cub/src/rendering/rotation_init.c cub/src/rendering/textures.c \
				cub/utils/ft_split.c cub/utils/gcollector.c cub/utils/gnl_utils.c \
				cub/utils/gnl.c  cub/utils/utils1.c cub/utils/utils2.c  \


BNS_SRCS	=	cub_bonus/cub_bonus.c cub_bonus/src/parsing/init_map_bonus.c \
				cub_bonus/src/parsing/init_elements_bonus.c cub_bonus/src/parsing/parsing_bonus.c \
				cub_bonus/src/rendering/hooks_bonus.c cub_bonus/src/rendering/raycasting_bonus.c \
				cub_bonus/src/rendering/draw_2D_map_bonus.c cub_bonus/src/rendering/mouse_hook.c\
				cub_bonus/src/rendering/rotation_init_bonus.c cub_bonus/src/rendering/textures_bonus.c \
				cub_bonus/src/rendering/doors.c \
				cub_bonus/utils/ft_split.c cub_bonus/utils/gcollector.c cub_bonus/utils/gnl_utils.c \
				cub_bonus/utils/gnl.c  cub_bonus/utils/utils1.c cub_bonus/utils/utils2.c \


BNS_OBJ			= $(BNS_SRCS:%.c=%.o)

LIBMLX		=	MLX42/build/libmlx42.a
LIBMLX_INC	=	-IMLX/include/MLX -Iinclude
OBJ			=	$(SRC:%.c=%.o)
HEADER		= 	cub3d/includes/cub_bonus.h
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    BREW_PREFIX	= $(shell brew --prefix)
    MLXFLG		= -Iinclude -L$(BREW_PREFIX)/lib -lglfw -lm -ldl -lX11 -lXext -lXcursor -lXfixes -lpthread
    $(info Building for Linux...)
endif

ifeq ($(UNAME_S),Darwin)
    MLXFLG		= -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit
    $(info Building for macOS...)
endif

all: $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(LIBMLX_INC) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXFLG) $(LIBMLX) $(CFLAGS) -o $(NAME)
	@echo "Done"

bonus : $(BNS_NAME)

$(BNS_NAME) : $(BNS_OBJ)
	@$(CC) $(BNS_OBJ) $(MLXFLG) $(LIBMLX) $(CFLAGS) -o $(BNS_NAME)
	@echo "Bonus Done"

clean:
	@rm -f $(OBJ) $(BNS_OBJ)

fclean: clean
	@rm -f $(NAME) $(BNS_NAME)

re: fclean all

.PHONY: clean all re fclean bonus