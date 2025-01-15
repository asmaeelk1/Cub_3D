NAME		=	cub3D
CC			= 	cc
CFLAGS		=	-Wall -Wextra -Iincludes -I./includes/ #-fsanitize=address -g
SRC			=	src/cub.c \
				src/parsing/parsing.c src/parsing/init_elements.c src/parsing/init_map.c\
				src/utils/gcollector.c src/utils/gnl.c src/utils/gnl_utils.c src/utils/utils1.c \
				src/utils/errors.c src/utils/ft_split.c src/utils/utils2.c \
				src/rendering/draw_utils.c src/rendering/map2D.c  \
				src/movement/p_hooks.c \

LIBMLX		=	MLX42/libmlx42.a
LIBMLX_INC	=	-IMLX/include/MLX -Iinclude
MLXFLG		=	-Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit
OBJ			=	$(SRC:%.c=%.o)
BNS_OBJ		=	$(BNS_SRCS:%.c=%.o)
HEADER		= 	includes/cub.h

all: $(NAME)

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(LIBMLX_INC)  -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(MLXFLG) $(LIBMLX)  -o $(NAME)
	@echo "Mandatory Done"

bonus : $(BNS_NAME)

$(BNS_NAME) : $(BNS_OBJ)
	@$(CC) $(CFLAGS) $(BNS_OBJ) -o $(BNS_NAME)
	@echo "Bonus Done"

clean:
	@rm -f $(OBJ) $(BNS_OBJ)

fclean: clean
	@rm -f  $(NAME) $(BNS_NAME)

re: fclean all

.PHONY: clean 