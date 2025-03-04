NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC =	ft_printf.c \
		ft_putstr.c \
		ft_putnbr.c \
		ft_putchar.c \
		ft_puthexa.c \
		ft_putaddr.c \
		ft_putnbr_unsigned.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean