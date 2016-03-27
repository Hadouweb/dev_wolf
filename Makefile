CC = gcc -Werror -Wextra -Wall

SRCPATH = ./srcs
INCPATH = ./includes

LIBFT = ./libft
MINILIBX = ./minilibx_macos

HEADER = -I $(LIBFT)/includes -I $(INCPATH) -I $(MINILIBX)

LIB = -L$(LIBFT) -lft -L$(MINILIBX) -lmlx -framework OpenGL -framework AppKit 

SRC = 	$(SRCPATH)/main.c\
		$(SRCPATH)/w_draw.c\
		$(SRCPATH)/w_event.c\

OBJ = $(SRC:.c=.o)

NAME = wolf3d

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C $(LIBFT)
	@make -C $(MINILIBX)
	@$(CC) $(HEADER) $(LIB) -o $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(HEADER) -o $@ -c $<
	@echo "\033[32m█\033[0m\c"

clean : 
	@make -C $(LIBFT) clean
	@make -C $(MINILIBX) clean
	rm -rf $(OBJ)

fclean : clean
	@make -C $(LIBFT) fclean
	@rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re