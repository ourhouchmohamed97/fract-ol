NAME = fractol
NAME_BONUS = fractol_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

DEP_MAN = ./include/fractol.h 
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

BON_DIR = ./bonus
DEP_BON = ./include/fractol_bonus.h

SRC_BON = $(BON_DIR)/main_bonus.c \
	$(BON_DIR)/color_bonus.c \
	$(BON_DIR)/mandelbrot_bonus.c \
	$(BON_DIR)/julia_bonus.c \
	$(BON_DIR)/exit_bonus.c \
	$(BON_DIR)/init_bonus.c \


OBJ_BON = $(SRC_BON:.c=.o)

LIBFT_DIR = ./libft_utils
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(DEP_MAN)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BON) $(LIBFT) $(DEP_BON)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(OBJ) $(LIBFT) -o $(NAME_BONUS)

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) $(OBJ) $(OBJ_BON)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all