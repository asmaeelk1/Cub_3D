NAME		=	cub3D
CC			= 	cc
<<<<<<< HEAD
CFLAGS		=	-Wall -Wextra -Werror -Iincludes -I./includes/ -fsanitize=address -g3
SRC			=	src/cub.c \
				src/parsing/parsing.c src/parsing/init_elements.c src/parsing/init_map.c\
				src/utils/gnl.c src/utils/gnl_utils.c src/utils/utils1.c src/utils/utils2.c \
				src/utils/errors.c src/utils/ft_split.c src/utils/gcollector.c\
				src/rendering/draw_utils.c src/rendering/map2D.c src/rendering/raycasting.c \
				src/movement/p_hooks.c \
=======
CFLAGS		=	-Wall -Wextra -Werror -Iincludes -I./includes/  #-fsanitize=address 
SRC			=	src/cub.c \
				src/mandatory/parsing/parsing.c src/mandatory/parsing/init_elements.c src/mandatory/parsing/init_map.c\
				src/utils/gcollector.c src/utils/gnl.c src/utils/gnl_utils.c src/utils/utils1.c \
				src/utils/errors.c src/utils/ft_split.c src/utils/utils2.c \
				src/mandatory/randring/draw_utils.c src/mandatory/randring/map2D.c  \
				src/mandatory/randring/hooks.c \
>>>>>>> main

LIBMLX		=	MLX42/build/libmlx42.a
LIBMLX_INC	=	-IMLX/include/MLX -Iinclude
OBJ			=	$(SRC:%.c=%.o)
BNS_OBJ		=	$(BNS_SRCS:%.c=%.o)
HEADER		= 	includes/cub.h
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
<<<<<<< HEAD
	@$(CC) $(CFLAGS) $(LIBMLX_INC) -c $< -o $@
	@echo "🛠️ Creating Objects!!"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXFLG) $(LIBMLX) $(CFLAGS) -o $(NAME)
	@echo "👌 Done"
=======
	@$(CC) $(CFLAGS) $(LIBMLX_INC)  -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXFLG) $(LIBMLX)  -o $(NAME)
	@echo "Mandatory Done"
>>>>>>> main

bonus: $(BNS_NAME)

$(BNS_NAME): $(BNS_OBJ)
	@$(CC) $(CFLAGS) $(BNS_OBJ) -o $(BNS_NAME)
	@echo "Bonus Done"

clean:
	@rm -f $(OBJ) $(BNS_OBJ)
<<<<<<< HEAD
	@echo "🧨 Deleting OBJS."

fclean: clean
	@rm -f $(NAME) $(BNS_NAME)
	@echo "💣 Destroy all"
=======

fclean: clean
	@rm -f  $(NAME) $(BNS_NAME)
>>>>>>> main

re: fclean all

.PHONY: clean all re fclean bonus