# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: Claude3.7 <cursor@42.fr>                   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/01 00:00:00 by Claude3.7         #+#    #+#              #
#    Updated: 2023/01/01 00:00:00 by Claude3.7        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs
RM = rm -f

SRCS = ft_printf.c ft_putchar.c ft_print_char.c
OBJS = $(SRCS:.c=.o)

HEADER = ft_printf.h

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) test_printf

fclean: clean
	$(RM) $(NAME)

re: fclean all

# テスト用ターゲット
test: $(NAME)
	$(CC) $(CFLAGS) main.c -L. -lftprintf -o test_printf
	./test_printf

.PHONY: all clean fclean re test 