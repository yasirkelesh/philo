# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ademirci <ademirci@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/22 14:26:55 by ademirci          #+#    #+#              #
#    Updated: 2022/08/28 18:52:14 by ademirci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAG = -Wall -Wextra -Werror
OPTION = -c
SRC = $(shell find ./mandatory -name "*.c")
BONUS = $(shell find ./bonus -name "*.c")
EXTRA = $(shell find ./extra -name "*.c")

all:
	@gcc $(FLAG) $(OPTION) $(SRC)
	@if [ -d "object" ]; then mv *.o ./object; else mkdir object; mv *.o ./object; fi
	@ar rc $(NAME) ./object/*.o

bonus: all
	@gcc $(FLAG) $(OPTION) $(BONUS)
	@mv *.o ./object
	@ar rc $(NAME) ./object/*.o

extra: all bonus
	@gcc $(FLAG) $(OPTION) $(EXTRA)
	@mv *.o ./object
	@ar rc $(NAME) ./object/*.o

clean:
	@rm -rf  object

fclean: clean
	@rm -rf $(NAME)

re: fclean all