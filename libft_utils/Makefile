NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

DEPS = ./libft/libft.h ./printf/ft_printf.h
LIB_DIR = ./libft
PRINTF_DIR = ./printf

LIBFT_SRCS = $(LIB_DIR)/ft_strlen.c \
	  		$(LIB_DIR)/ft_strncmp.c \
			$(LIB_DIR)/ft_atod.c \

PRINTF_SRCS = $(PRINTF_DIR)/ft_printf.c \
		$(PRINTF_DIR)/ft_putstr.c \
		$(PRINTF_DIR)/ft_putnbr.c \
		$(PRINTF_DIR)/ft_putchar.c \
		$(PRINTF_DIR)/ft_puthexa.c \
		$(PRINTF_DIR)/ft_putaddr.c \
		$(PRINTF_DIR)/ft_putnbr_unsigned.c \

SRC = $(LIBFT_SRCS) $(PRINTF_SRCS)

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean