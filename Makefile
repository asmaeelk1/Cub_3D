NAME		=	cub3D
CC			= 	cc
CFLAGS		=	-Wall -Wextra -Werror -Iincludes -I./includes/ -fsanitize=address -g3
SRC			=	cub3d/cub.c cub3d/src/parsing/init_map.c \
				cub3d/src/parsing/init_elements.c cub3d/src/parsing/parsing.c \
				cub3d/src/rendering/hooks.c cub3d/src/rendering/raycasting.c \
				cub3d/src/rendering/rotation_init.c cub3d/src/rendering/textures.c \
				cub3d/utils/ft_split.c cub3d/utils/gcollector.c cub3d/utils/gnl_utils.c \
				cub3d/utils/gnl.c  cub3d/utils/utils1.c cub3d/utils/utils2.c  \

LIBMLX		=	MLX42/build/libmlx42.a
LIBMLX_INC	=	-IMLX/include/MLX -Iinclude
OBJ			=	$(SRC:%.c=%.o)
HEADER		= 	cub3d/includes/cub.h
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
	@echo "🛠️ Creating Objects!!"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXFLG) $(LIBMLX) $(CFLAGS) -o $(NAME)
	@echo "👌 Done"

clean:
	@rm -f $(OBJ) $(BNS_OBJ)
	@echo "🧨 Deleting OBJS."

fclean: clean
	@rm -f $(NAME) $(BNS_NAME)
	@echo "💣 Destroy all"

re: fclean all

.PHONY: clean all re fclean bonus