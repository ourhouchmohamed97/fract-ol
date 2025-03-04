NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

INC_DIR = ./include/fractol.h 
MAN_DIR = ./mandatory
MLX_LIB = ./minilibx/libmlx.a
MLX_FLAGS = $(MLX_LIB) -framework OpenGL -framework AppKit

SRC = $(MAN_DIR)/main.c \
	$(MAN_DIR)/color.c \
	$(MAN_DIR)/mandelbrot.c \
	$(MAN_DIR)/m_set.c \
	$(MAN_DIR)/j_set.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(INC_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all