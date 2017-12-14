# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/31 18:24:54 by dkovalen          #+#    #+#              #
#    Updated: 2017/05/07 19:25:55 by dkovalen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fdf

FLAGS	= -Wall -Wextra -Werror

MLX		= -lmlx -framework OpenGL -framework AppKit

LIBA	= ./libft/libftprintf.a

SRC		= main.c read_map.c fill_struct.c brezen.c line.c line_grad.c colors.c keys1.c keys2.c

SRC_O	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC_O)
	@ make -C ./libft
	gcc $(FLAGS) $(MLX) $(SRC_O) $(LIBA) -o $(NAME)

%.o: %.c
	@gcc -c -Wall -Wextra -Werror -o $@ $<

clean:
	@ make clean -C ./libft
	@rm -f $(SRC_O)

fclean: clean
	@rm -f $(NAME) $(LIBA)
	@echo "cleaned FdF"

re: fclean all
