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
	$(MAN_DIR)/julia.c \
	$(MAN_DIR)/exit.c \
	$(MAN_DIR)/init.c \

OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft_utils
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(INC_DIR)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all