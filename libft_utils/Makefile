NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

DEPS = ./libft/libft.h ./printf/ft_printf.h

LIBFT_SRCS = ./libft/ft_strlen.c \
	  		./libft/ft_strncmp.c \
			./libft/ft_atof.c \

PRINTF_SRCS = ./printf/ft_printf.c \
		./printf/ft_putstr.c \
		./printf/ft_putnbr.c \
		./printf/ft_putchar.c \
		./printf/ft_puthexa.c \
		./printf/ft_putaddr.c \
		./printf/ft_putnbr_unsigned.c \

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