NAME    = philo
CC      = gcc
DEBUG   = -g
FLAG    = -Wall -Wextra -Werror
SRC     = philo.c init.c thread.c life_loop.c utils.c
LIBFT   = ./libft/libft.a

all:
	@make lib
	@$(CC) $(FLAG) $(SRC) -o $(NAME) $(LIBFT)
	@echo "\033[1;32mPHILOSOPHERS Compiled\033[0m"

lib:
	@make fclean -C ./libft
	@make extra -C ./libft
	@echo "\033[1;32mLIBFT Compiled\033[0m"
	
clean:
	@make fclean -C ./libft
	@rm -f ./ft_printf/*.o
fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;32mCleaned\033[0m" 

debug:
	@$(CC) $(DEBUG) $(FLAG) $(SRC) -o $(NAME) $(LIBFT)
	@echo "\033[1;32mPHILOSOPHERS Compiled for debugging\033[0m"

leaks: debug
	@echo "\033[1;32mPHILOSOPHERS Leaks report\033[0m"
	@leaks -atExit -- ./$(NAME)

re: fclean all