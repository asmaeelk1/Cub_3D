NAME		=	cub3D
CC			= 	cc
CFLAGS		=	-Wall -Wextra -Werror -Iincludes -I./includes/ -fsanitize=address -g3
SRC			=	mandatory/cub.c \
				mandatory/src/parsing/parsing.c mandatory/src/parsing/init_elements.c mandatory/src/parsing/init_map.c\
				mandatory/utils/gcollector.c mandatory/utils/gnl.c mandatory/utils/gnl_utils.c mandatory/utils/utils1.c \
				mandatory/utils/errors.c mandatory/utils/ft_split.c mandatory/utils/utils2.c \
				mandatory/src/rendering/hooks.c mandatory/src/rendering/raycasting.c \
				mandatory/src/rendering/ray_init.c mandatory/src/rendering/textures.c \

LIBMLX		=	MLX42/build/libmlx42.a
LIBMLX_INC	=	-IMLX/include/MLX -Iinclude
OBJ			=	$(SRC:%.c=%.o)
BNS_OBJ		=	$(BNS_SRCS:%.c=%.o)
HEADER		= 	mandatory/includes/cub.h
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

bonus: $(BNS_NAME)

$(BNS_NAME): $(BNS_OBJ)
	@$(CC) $(CFLAGS) $(BNS_OBJ) -o $(BNS_NAME)
	@echo "Bonus Done"

clean:
	@rm -f $(OBJ) $(BNS_OBJ)
	@echo "🧨 Deleting OBJS."

fclean: clean
	@rm -f $(NAME) $(BNS_NAME)
	@echo "💣 Destroy all"

re: fclean all

.PHONY: clean all re fclean bonus