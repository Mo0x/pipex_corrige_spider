NAME = pipex
NAME_BONUS = pipex_bonus
CC = gcc 
SRCS = ./srcs/main.c ./srcs/pipex.c ./srcs/ft_error.c ./srcs/path_and_cmd_finder.c
SRCS_BONUS = ./srcs_bonus/main_bonus.c ./srcs_bonus/pipex_bonus.c ./srcs_bonus/ft_error_bonus.c ./srcs_bonus/path_and_cmd_finder_bonus.c
OBJS = $(patsubst %.c, %.o, $(SRCS))
OBJS_BONUS = $(patsubst %.c, %.o, $(SRCS_BONUS))
BONUST = .bonus
INCDIRS = ./includes
CFLAGS = -Wall -Wextra -Werror -I$(INCDIRS) -g3 -fsanitize=address

all : $(NAME)

$(NAME) : $(OBJS)
	make -C ./libft/
	mv ./libft/libft.a .
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L. -lft

bonus : $(BONUST)

$(BONUST) : $(OBJS_BONUS)
	touch $(BONUST)
	make -C ./libft/
	mv ./libft/libft.a .
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) -L. -lft
	
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean :
	make clean -C ./libft/
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	rm -rf $(NAME) $(NAME_BONUS) libft.a

re : fclean all

.PHONY : all bonus clean fclean re
